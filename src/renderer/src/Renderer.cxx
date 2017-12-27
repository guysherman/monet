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


// C Standard Headers


// Boost Headers

// 3rd Party Headers

// GTK Headers


// Our Headers
#include "../include/renderer/Renderer.h"

namespace monet
{
    namespace renderer
    {
        Renderer::Renderer() {}
        Renderer::~Renderer() {}

        void Renderer::Draw() 
        {
            // inside this function it's safe to use GL; the given
			// #GdkGLContext has been made current to the drawable
			// surface used by the #GtkGLArea and the viewport has
			// already been set to be the size of the allocation

			// we can start by clearing the buffer
			glClearColor (0.4f, 0.6f, 0.95f, 1.0f);
			glClear (GL_COLOR_BUFFER_BIT);

			
        }
    }
}

