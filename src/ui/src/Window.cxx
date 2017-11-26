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


// C++ Standard Headers
#include <memory>
#include <string>
#include <iostream>
// C Standard Headers


// Boost Headers

// 3rd Party Headers
#define GLM_PRECISION_MEDIUMP_INT
#define GLM_PRECISION_HIGHP_FLOAT
#include <glm/vec2.hpp>

// GTK Headers


// Our Headers
#include "../include/ui/AppDelegate.h"
#include "../include/ui/Window.h"

namespace monet
{
	namespace ui
	{
		Window::Window(std::string windowTitle, glm::vec2 windowSize) :
			nativeWindow(nullptr),
			windowTitle(windowTitle),
			windowSize(windowSize)
		{
			#ifndef WIN32
				glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
				glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 2 );
				glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
				glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
			#endif

			this->nativeWindow = glfwCreateWindow( windowSize.x, windowSize.y, windowTitle.c_str(), NULL, NULL );
			if ( !this->nativeWindow ) {
				fprintf( stderr, "ERROR: could not open window with GLFW3\n" );
				glfwTerminate();
				exit(EXIT_FAILURE);
			}
		}

		Window::~Window()
		{

		}

		GLFWwindow *Window::GetNativeWindow()
		{
			return this->nativeWindow;
		}

		void Window::MouseButtonEvent(int button, int action, int mods) 
		{
			double xpos, ypos;
			glfwGetCursorPos(this->nativeWindow, &xpos, &ypos);
			std::cout << "Button: " << xpos << ", " << ypos << std::endl;

		}
		void Window::MousePositionEvent(double xpos, double ypos) 
		{
			std::cout << "Move: " << xpos << ", " << ypos << std::endl;
		}

		void Window::ScrollEvent(double xoffset, double yoffset) {}
		void Window::KeyEvent(int key, int scancode, int action, int mods) 
		{
			if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			{
				glfwSetWindowShouldClose(this->nativeWindow, GLFW_TRUE);
			}
		}

	}
}
