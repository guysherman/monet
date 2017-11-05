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
#include <string>
#include <iostream>

// C Standard Headers


// Boost Headers

// 3rd Party Headers


// GTK Headers


// Our Headers

#include "../include/ui/AppDelegate.h"

namespace monet
{
	namespace ui
	{
		AppDelegate *AppDelegate::instance = nullptr;
	
		static void error_callback(int error, const char* description)
		{
			std::cerr << "Error: " << description << std::endl;
		}
	
		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			// if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			// 	glfwSetWindowShouldClose(window, GLFW_TRUE);
			if (nullptr != AppDelegate::instance)
			{
				AppDelegate::instance->KeyEvent(window, key, scancode, action, mods);
			}
		}
	
		static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
		{
			if (nullptr != AppDelegate::instance)
			{
				AppDelegate::instance->MouseButtonEvent(window, button, action, mods);
			}
		}
	
		static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
		{
			if(nullptr != AppDelegate::instance)
			{
				AppDelegate::instance->MousePositionEvent(window, xpos, ypos);
			}
		}
	
		static void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
		{
			if (nullptr != AppDelegate::instance)
			{
				AppDelegate::instance->ScrollEvent(window, xoffset, yoffset);
			}
		}
	
		AppDelegate::AppDelegate(int width, int height, std::string windowTitle)
		{
			this->windowTitle = windowTitle;
			glfwSetErrorCallback(error_callback);
			/* start GL context and O/S window using the GLFW helper library */
			if ( !glfwInit() ) {
				std::cerr << "ERROR: could not start GLFW3" << std::endl;
				exit(EXIT_FAILURE);
			}
	
		#ifndef WIN32
			glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
			glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 2 );
			glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
			glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
		#endif
	
			window = glfwCreateWindow( width, height, windowTitle.c_str(), NULL, NULL );
			if ( !window ) {
				fprintf( stderr, "ERROR: could not open window with GLFW3\n" );
				glfwTerminate();
				exit(EXIT_FAILURE);
			}

			glfwSetKeyCallback(window, key_callback);
			glfwSetMouseButtonCallback(window, mouse_button_callback);
			glfwSetCursorPosCallback(window, cursor_position_callback);
			glfwSetScrollCallback(window, scroll_callback);
		}
	
		AppDelegate::~AppDelegate()
		{
	
		}
	
		void AppDelegate::KeyEvent(GLFWwindow *window, int key, int scancode, int action, int mods)
		{
			if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			{
				glfwSetWindowShouldClose(window, GLFW_TRUE);
			}
		}
	
		void AppDelegate::MouseButtonEvent(GLFWwindow *window, int button, int action, int mods)
		{
			double xpos, ypos;
			glfwGetCursorPos(window, &xpos, &ypos);
			
		}
	
		void AppDelegate::MousePositionEvent(GLFWwindow *window, double xpos, double ypos)
		{
			
		}
	
		void AppDelegate::ScrollEvent(GLFWwindow *window, double xoffset, double yoffset)
		{
			
		}
	
		void AppDelegate::Run()
		{
			while ( !glfwWindowShouldClose( window ) )
			{
				
				
			
				glfwWaitEventsTimeout(0.016);
				
				//glfwPollEvents();
			}
		}
	}
}
