#ifndef _TEXTURE_H_
#define _TEXTURE_H_

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

namespace monet
{
    namespace renderer
	{
		class Texture
		{
		public:
			Texture();
			virtual ~Texture();

			GLuint GetTextureId();
			GLuint GetTextureUnit();
		
		private:
			GLuint textureId;
		};
	}
}

#endif //_TEXTURE_H_