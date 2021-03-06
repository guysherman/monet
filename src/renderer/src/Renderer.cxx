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

#include "../pch/pch.h"

// GLEW
#include <GL/glew.h>

// C++ Standard Headers
#include <iostream>
#include <memory>

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
#include "../include/renderer/ShaderProgram.h"
#include "../include/renderer/Texture.h"
#include "../include/renderer/RenderPasses.h"
#include "../include/renderer/IRenderPass.h"
#include "../include/renderer/IRenderPassConfig.h"
#include "../include/renderer/DemosaicRenderPass.h"
#include "../include/renderer/DisplayRenderPass.h"

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
        Renderer::Renderer() : viewSize(glm::vec2(0.0f)), imageAspectRatio(2.0f)
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

			

			

			// we can start by clearing the buffer
			glClearColor(0x30 / 255.0f, 0x30 / 255.0f, 0x30 / 255.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

			std::shared_ptr<IRenderPass> prev = nullptr;

			for (auto it = processingPipeline.begin(); it != processingPipeline.end(); ++it)
			{
				auto pass = *it;
				pass->Execute(this, prev);
				prev = pass;
			}

			glFlush();
        }

		void Renderer::BindShaderProgram(GLuint programId)
		{
			// -- BIND SHADER
			glUseProgram(programId);
		}
		
		void Renderer::SetMvpMatrix(std::string uniformName, GLuint programId, float imageViewAspectRatio)
		{
			auto model = glm::mat4(1.0f);
			auto view = glm::lookAt(glm::vec3(0.5f, 0.5f, 1.0f), glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			
			float l, r, t, b;
			//float imageAspectRatio = 2.0f;
			float aspectRatio = (viewSize.x / viewSize.y) / imageViewAspectRatio;

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
			
			// -- SET MVP MATRIX
			int matrix_location = glGetUniformLocation (programId, uniformName.c_str());
			glUniformMatrix4fv(matrix_location, 1, GL_FALSE, glm::value_ptr(mvp));
		}

		void Renderer::SetMvpMatrixForRenderTexture(std::string uniformName, GLuint programId)
		{
			auto model = glm::mat4(1.0f);
			auto view = glm::lookAt(glm::vec3(0.5f, 0.5f, 1.0f), glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			
			float l, r, t, b;
			l = -0.5f;
			r = 0.5f;
			t = 0.5f;
			b = -0.5f;

			auto projection = glm::ortho(l, r, t, b, -1.0f, 1.0f);

			auto mvp = projection * view * model;

			int matrix_location = glGetUniformLocation (programId, uniformName.c_str());
			glUniformMatrix4fv(matrix_location, 1, GL_FALSE, glm::value_ptr(mvp));

		}

		void Renderer::BindTexture(std::weak_ptr<Texture> texture)
		{
			auto tex = texture.lock();
			if (tex != nullptr)
			{
				// -- BIND TEXTURE
				glActiveTexture( tex->GetTextureUnit() );
				glBindTexture( tex->GetTarget(), tex->GetTextureId() );
				glTexParameteri( tex->GetTarget(), GL_TEXTURE_WRAP_S, tex->GetWrapS() );
				glTexParameteri( tex->GetTarget(), GL_TEXTURE_WRAP_T, tex->GetWrapT() );
				glTexParameteri( tex->GetTarget(), GL_TEXTURE_MAG_FILTER, tex->GetMagFilter() );
				glTexParameteri( tex->GetTarget(), GL_TEXTURE_MIN_FILTER, tex->GetMinFilter() );
				glTexParameterf( tex->GetTarget(), GL_TEXTURE_MAX_ANISOTROPY_EXT, tex->GetMaxAniso() );
			}
		}

		void Renderer::RenderGeometry(std::weak_ptr<Geometry> geometry)
		{
			auto geo = geometry.lock();
			if (geo != nullptr)
			{
				// DRAW GEOMETRY
				glBindVertexArray(geo->GetVaoId());
				glDrawElements(GL_TRIANGLES, geo->GetNumElements(), GL_UNSIGNED_INT, (void *)0);
			}
		}

		void Renderer::MapTextureUnit(GLuint textureUnit, std::string uniformName, GLuint programId)
		{
			GLuint uniformLocation = glGetUniformLocation(programId, uniformName.c_str());
			glUniform1i(uniformLocation, textureUnit);
		}

		void Renderer::BindRenderTexture(std::weak_ptr<Texture> texture, GLuint *fb, GLenum *buffers)
		{
			glGenFramebuffers(1, fb);
			glBindFramebuffer(GL_FRAMEBUFFER, *fb);

			auto tex = texture.lock();
			if (nullptr != tex)
			{
				glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, tex->GetTextureId(), 0);
				*buffers = GL_COLOR_ATTACHMENT0;
				glDrawBuffers(1, buffers);
			}
		}

		void Renderer::GetCurrentFboIds(GLint *dfbo, GLint *rfbo)
		{
			glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, dfbo);
			glGetIntegerv(GL_READ_FRAMEBUFFER_BINDING, rfbo);
		}

		void Renderer::DeleteFrameBuffer(GLuint *fbId)
		{
			glDeleteFramebuffers(1, fbId);
		}

		void Renderer::BindDefaultFrameBuffers(GLint *dfbo, GLint *rfbo)
		{
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, *dfbo);
			glBindFramebuffer(GL_READ_FRAMEBUFFER, *rfbo);
		}

		void Renderer::ResizeView(float width, float height)
		{
			viewSize = glm::vec2(width, height);
		}

		void Renderer::SetViewport(float x, float y, float width, float height)
		{
			glViewport(x, y, width, height);
		}

		void Renderer::RestoreViewportToViewSize()
		{
			glViewport(0, 0, viewSize.x, viewSize.y);
		}

		void Renderer::SetImageAspectRatio(float aspect)
		{
			imageAspectRatio = aspect;
		}

		bool Renderer::AddRenderPass(RenderPass pass, IRenderPassConfig *config)
		{
			//processingPipeline.push_back(pass);
			switch (pass) 
			{
				case RenderPass::DEMOSAIC:
				{
					DemosaicRenderPassConfig *cfg = dynamic_cast<DemosaicRenderPassConfig*>(config);
					if (cfg != nullptr)
					{
						processingPipeline.push_back(std::shared_ptr<IRenderPass>(new DemosaicRenderPass(cfg)));
						return true;
					}
					else
					{
						return false;
					}
					break;
				}
				case RenderPass::DISPLAY:
				{
					processingPipeline.push_back(std::shared_ptr<IRenderPass>(new DisplayRenderPass()));
					return true;
					break;
				}
					
			}
		}

		void Renderer::ClearProcessingPipeline()
		{
			processingPipeline.clear();
		}

		std::vector< std::weak_ptr<IRenderPass> > Renderer::GetProcessingPipeline()
		{
			std::vector< std::weak_ptr<IRenderPass> > result;
			for (auto it = processingPipeline.begin(); it != processingPipeline.end(); ++it)
			{
				result.push_back(std::weak_ptr<IRenderPass>(*it));
			}

			return result;
		}

		template <>	void Renderer::SetUniformValue(std::string uniformName, GLuint programId, float value)
		{
			GLuint uniformLocation = glGetUniformLocation(programId, uniformName.c_str());
			glUniform1f(uniformLocation, value);
		}

		template <>	void Renderer::SetUniformValue(std::string uniformName, GLuint programId, int32_t value)
		{
			GLuint uniformLocation = glGetUniformLocation(programId, uniformName.c_str());
			glUniform1i(uniformLocation, value);
		}

		template <>	void Renderer::SetUniformValue(std::string uniformName, GLuint programId, uint32_t value)
		{
			GLuint uniformLocation = glGetUniformLocation(programId, uniformName.c_str());
			glUniform1ui(uniformLocation, value);
		}

    }
}

