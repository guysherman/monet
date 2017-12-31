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


// C++ Standard Headers
#include <cstdint>

// C Standard Headers


// Boost Headers

// 3rd Party Headers

// GTK Headers


// Our Headers
#include "../include/renderer/Texture.h"

namespace monet
{
    namespace renderer
	{
		Texture::Texture()
		: textureId(0)
		{
			uint8_t data[16] = {
				0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF
			};

			glGenTextures(1, &this->textureId);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, this->textureId);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 2, 2, 0, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, data);
		}

		Texture::~Texture()
		{
			glDeleteTextures(1, &this->textureId);
		}

		GLuint Texture::GetTextureId()
		{
			return textureId;
		}

		GLuint Texture::GetTextureUnit()
		{
			return GL_TEXTURE0;
		}
	}
}

