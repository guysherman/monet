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
#include <cstdint>
#include <thread>
// C Standard Headers


// Boost Headers

// 3rd Party Headers
#include <RawSpeed-API.h>
#include <metadata/CameraMetadataException.h>
#include <io/FileIOException.h>

// GTK Headers


// Our Headers
#include "../include/renderer/Texture.h"



namespace monet
{
    namespace renderer
	{
		//Texture::Texture(std::string filePath)
		Texture::Texture(uint8_t *data, uint32_t width, uint32_t height, GLuint textureUnit, GLuint target, GLuint internalFormat, GLuint format, GLuint type, GLuint minMag, GLuint wrap)
		: textureId(0), textureUnit(textureUnit), target(target), minMag(minMag), wrap(wrap)
		{
			glGenTextures(1, &this->textureId);
			glActiveTexture(this->textureUnit);
			glBindTexture(this->target, this->textureId);
			glTexImage2D(this->target, 0, internalFormat, width, height, 0, format, type, data);

			size = glm::vec2(width, height);
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
			return textureUnit;
		}

		GLuint Texture::GetTarget()
		{
			return target;
		}

		GLenum Texture::GetWrapS()  
		{
			return wrap;
		}

		GLenum Texture::GetWrapT()  
		{
			return wrap;
		}

		GLenum Texture::GetMinFilter() 
		{
			return minMag;
		}

		GLenum Texture::GetMagFilter() 
		{
			return minMag;
		}

		GLenum Texture::GetMaxAniso()  
		{
			return 1.0f;
		}

		glm::vec2 Texture::GetSize()
		{
			return size;
		}
	}
}

