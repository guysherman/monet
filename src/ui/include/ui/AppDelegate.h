#ifndef __APPDELEGATE_H__
#define __APPDELEGATE_H__
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

// C Standard Headers


// Boost Headers

// 3rd Party Headers
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// GTK Headers


// Our Headers



#ifdef __APPLE__
#define SCROLL_SENSITIVITY 1.0f
#else 
#define SCROLL_SENSITIVITY 0.05f
#endif


namespace monet
{
	
	namespace ui
	{
		class AppDelegate
		{
		public:
			AppDelegate(int width, int height, std::string windowTitle);
			virtual ~AppDelegate();
	
			void MouseButtonEvent(GLFWwindow* window, int button, int action, int mods);
			void MousePositionEvent(GLFWwindow* window, double xpos, double ypos);
			void ScrollEvent(GLFWwindow* window, double xoffset, double yoffset);
			void KeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods);
	
			void Run();
	
			static AppDelegate *instance;
	
		private:
			GLFWwindow* window;
			std::string windowTitle;
			
	
	
	
		};
	}
	
}

#endif // __APPDELEGATE_H__