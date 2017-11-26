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
#include <memory>

// C Standard Headers


// Boost Headers

// 3rd Party Headers


// GTK Headers


// Our Headers

#include "../include/ui/AppDelegate.h"
#include "../include/ui/Window.h"

namespace monet
{
	namespace ui
	{
		AppDelegate *AppDelegate::instance = nullptr;
	
		static void error_callback(int error, const char* description)
		{
			std::cerr << "Error: " << description << std::endl;
		}
	
		static void key_callback(GLFWwindow* nativeWindow, int key, int scancode, int action, int mods)
		{
			// if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			// 	glfwSetWindowShouldClose(window, GLFW_TRUE);
			if (nullptr != AppDelegate::instance)
			{
				auto window = AppDelegate::instance->GetWindow(nativeWindow);
				if (nullptr != window)
				{
					window->KeyEvent(key, scancode, action, mods);
				}
			}
		}
	
		static void mouse_button_callback(GLFWwindow* nativeWindow, int button, int action, int mods)
		{
			if (nullptr != AppDelegate::instance)
			{
				auto window = AppDelegate::instance->GetWindow(nativeWindow);
				if (nullptr != window)
				{
					window->MouseButtonEvent(button, action, mods);
				}
			}
		}
	
		static void cursor_position_callback(GLFWwindow* nativeWindow, double xpos, double ypos)
		{
			if(nullptr != AppDelegate::instance)
			{
				auto window = AppDelegate::instance->GetWindow(nativeWindow);
				if (nullptr != window)
				{
					window->MousePositionEvent(xpos, ypos);
				}
			}
		}
	
		static void scroll_callback(GLFWwindow *nativeWindow, double xoffset, double yoffset)
		{
			if (nullptr != AppDelegate::instance)
			{
				auto window = AppDelegate::instance->GetWindow(nativeWindow);
				if (nullptr != window)
				{
					window->ScrollEvent(xoffset, yoffset);
				}
			}
		}
	
		AppDelegate::AppDelegate()
		{
			
			glfwSetErrorCallback(error_callback);
			/* start GL context and O/S window using the GLFW helper library */
			if ( !glfwInit() ) {
				std::cerr << "ERROR: could not start GLFW3" << std::endl;
				exit(EXIT_FAILURE);
			}
	
		

			
		}
	
		AppDelegate::~AppDelegate()
		{
	
		}

		std::shared_ptr<monet::ui::Window> AppDelegate::GetWindow(GLFWwindow *nativeWindow)
		{
			auto itWindow = windowMappings.find(nativeWindow);
			if (itWindow != windowMappings.end())
			{
				return itWindow->second;
			}

			return nullptr;
		}
	
		// void AppDelegate::KeyEvent(GLFWwindow *window, int key, int scancode, int action, int mods)
		// {
		// 	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		// 	{
		// 		glfwSetWindowShouldClose(window, GLFW_TRUE);
		// 	}
		// }
	
		// void AppDelegate::MouseButtonEvent(GLFWwindow *window, int button, int action, int mods)
		// {
		// 	double xpos, ypos;
		// 	glfwGetCursorPos(window, &xpos, &ypos);
			
		// }
	
		// void AppDelegate::MousePositionEvent(GLFWwindow *window, double xpos, double ypos)
		// {
			
		// }
	
		// void AppDelegate::ScrollEvent(GLFWwindow *window, double xoffset, double yoffset)
		// {
			
		// }
	
		void AppDelegate::Run(std::shared_ptr<monet::ui::Window> window)
		{
			auto glfwWindow = window->GetNativeWindow();

			windowMappings[glfwWindow] = window;
			
			glfwSetKeyCallback(glfwWindow, key_callback);
			glfwSetMouseButtonCallback(glfwWindow, mouse_button_callback);
			glfwSetCursorPosCallback(glfwWindow, cursor_position_callback);
			glfwSetScrollCallback(glfwWindow, scroll_callback);
			
			
			while ( !glfwWindowShouldClose( glfwWindow ) )
			{
				
				
			
				glfwWaitEventsTimeout(0.016);
				
				//glfwPollEvents();
			}
		}
	}
}
