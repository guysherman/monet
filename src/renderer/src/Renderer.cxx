/*
	Monet is an open-source platform for building GPU-accelerated image
	processing applications.
	Copyright (C) 2017  Guy Sherman

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

	Contact the author via https://github.com/guysherman
*/

// GLEW
#include <GL/glew.h>

// C++ Standard Headers
#include <iostream>

// C Standard Headers


// Boost Headers

// 3rd Party Headers
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// GTK Headers


// Our Headers
#include "../include/renderer/Renderer.h"
#include "../include/renderer/Geometry.h"
#include "../include/renderer/RenderPass.h"

void openglCallbackFunction(GLenum source,
							GLenum type,
							GLuint id,
							GLenum severity,
							GLsizei length,
							const GLchar* message,
							const void* userParam)
{
	
	std::cout << "---------------------opengl-callback-start------------" << std::endl;
	std::cout << "message: "<< message << std::endl;
	std::cout << "type: ";
	switch (type) {
	case GL_DEBUG_TYPE_ERROR:
		std::cout << "ERROR";
		break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
		std::cout << "DEPRECATED_BEHAVIOR";
		break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
		std::cout << "UNDEFINED_BEHAVIOR";
		break;
	case GL_DEBUG_TYPE_PORTABILITY:
		std::cout << "PORTABILITY";
		break;
	case GL_DEBUG_TYPE_PERFORMANCE:
		std::cout << "PERFORMANCE";
		break;
	case GL_DEBUG_TYPE_OTHER:
		std::cout << "OTHER";
		break;
	}
	std::cout << std::endl;

	std::cout << "id: "<<id << std::endl;
	std::cout << "severity: ";
	switch (severity){
	case GL_DEBUG_SEVERITY_LOW:
		std::cout << "LOW";
		break;
	case GL_DEBUG_SEVERITY_MEDIUM:
		std::cout << "MEDIUM";
		break;
	case GL_DEBUG_SEVERITY_HIGH:
		std::cout << "HIGH";
		break;
	}
	std::cout << std::endl;
	std::cout << "---------------------opengl-callback-end--------------" << std::endl;
}


namespace monet
{
    namespace renderer
    {
        Renderer::Renderer() : viewSize(glm::vec2(0.0f)), imageAspectRatio(1.0f)
		{
			glewExperimental = GL_TRUE;
			glewInit();

			const GLubyte *renderer;
			const GLubyte *version;

			/* get version info */
			renderer = glGetString( GL_RENDERER ); /* get renderer string */
			version = glGetString( GL_VERSION );	 /* version as a string */
			std::cerr << "Renderer: " << renderer << std::endl;
			std::cerr << "OpenGL version supported: " << version << std::endl;
			
			if(glDebugMessageCallback)
			{
				std::cout << "Register OpenGL debug callback " << std::endl;
				glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
				glDebugMessageCallback(openglCallbackFunction, nullptr);
				GLuint unusedIds = 0;
				glDebugMessageControl(GL_DONT_CARE,
					GL_DONT_CARE,
					GL_DONT_CARE,
					0,
					&unusedIds,
					true);
			}
		}

        Renderer::~Renderer() {}

        void Renderer::Draw() 
        {
            // inside this function it's safe to use GL; the given
			// #GdkGLContext has been made current to the drawable
			// surface used by the #GtkGLArea and the viewport has
			// already been set to be the size of the allocation

			static Geometry *quad = nullptr;
			static RenderPass *pass = nullptr;
			static float clear_r = 0.0f;
			if (nullptr == quad)
			{
				quad = new Geometry();
			}

			if (nullptr == pass)
			{
				pass = new RenderPass();
			}

			int matrix_location = glGetUniformLocation (pass->GetProgramId(), "matrix");

			auto model = glm::mat4(1.0f);
			auto view = glm::lookAt(glm::vec3(0.5f, 0.5f, 1.0f), glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			
			float l, r, t, b;
			//float imageAspectRatio = 2.0f;
			float aspectRatio = (viewSize.x / viewSize.y) / imageAspectRatio;

			if (aspectRatio < 1.0f) // Tall
			{
				float invAspectRatio = 1.0f / aspectRatio;
				l = -0.51f;
				r =  0.51f;
				t = -0.51f * invAspectRatio;
				b =  0.51f * invAspectRatio;
			}
			else // Wide
			{
				l = -0.51f * aspectRatio;
				r =  0.51f * aspectRatio;
				t = -0.51f;
				b =  0.51f;
			}

			auto projection = glm::ortho(l, r, t, b, -1.0f, 1.0f);
			
			
			auto mvp = projection * view * model;

			// we can start by clearing the buffer
			glClearColor(clear_r, 0.6f, 0.95f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

			glUseProgram(pass->GetProgramId());
			glUniformMatrix4fv(matrix_location, 1, GL_FALSE, glm::value_ptr(mvp));
			glBindVertexArray(quad->GetVaoId());
			glDrawElements(GL_TRIANGLES, quad->GetNumElements(), GL_UNSIGNED_INT, (void *)0);

			clear_r += 0.1f;
			if (clear_r >= 1.0f)
			{
				clear_r = 0.0f;
			}

			glFlush();
        }

		void Renderer::ResizeView(float width, float height)
		{
			viewSize = glm::vec2(width, height);
		}

		void Renderer::SetImageAspectRatio(float aspect)
		{
			imageAspectRatio = aspect;
		}

    }
}

