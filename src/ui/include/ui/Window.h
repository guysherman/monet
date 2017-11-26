#ifndef __WINDOW_H__
#define __WINDOW_H__
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
// C Standard Headers


// Boost Headers

// 3rd Party Headers
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_PRECISION_MEDIUMP_INT
#define GLM_PRECISION_HIGHP_FLOAT
#include <glm/vec2.hpp>
// GTK Headers


// Our Headers



namespace monet
{
	namespace ui
	{
		
		class Window
		{
		public:

			Window(std::string windowTitle, glm::vec2 windowSize);
			virtual ~Window();

			GLFWwindow *GetNativeWindow();

			void MouseButtonEvent(int button, int action, int mods);
			void MousePositionEvent(double xpos, double ypos);
			void ScrollEvent(double xoffset, double yoffset);
			void KeyEvent(int key, int scancode, int action, int mods);
			
		private:
			GLFWwindow *nativeWindow;
			//AppDelegate *appDelegate;
			std::string windowTitle;
			glm::vec2 windowSize;
		};
	}
}

#endif // __WINDOW_H__