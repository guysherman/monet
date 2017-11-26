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
#include <memory>
#include <map>
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
		
		class Window;

		class AppDelegate
		{
		public:
			AppDelegate();
			virtual ~AppDelegate();
	
			void Run(std::shared_ptr<monet::ui::Window> window);
			std::shared_ptr<monet::ui::Window> GetWindow(GLFWwindow *nativeWindow);
	
			static AppDelegate *instance;
	
		private:
			std::map< GLFWwindow*, std::shared_ptr<monet::ui::Window> > windowMappings;
	
	
		};
	}
	
}

#endif // __APPDELEGATE_H__