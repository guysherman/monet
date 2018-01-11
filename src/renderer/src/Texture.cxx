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

int rawspeed_get_number_of_processor_cores()
{
	return std::thread::hardware_concurrency();
}

namespace monet
{
    namespace renderer
	{
		Texture::Texture(std::string filePath)
		: textureId(0)
		{
			try
			{
				rawspeed::CameraMetaData *metadata = new rawspeed::CameraMetaData("assets/cameras.xml");
				
				rawspeed::FileReader reader(filePath.c_str());
				std::unique_ptr<const rawspeed::Buffer> map = reader.readFile();
				
				rawspeed::RawParser parser(map.get());
				std::unique_ptr<rawspeed::RawDecoder> decoder = parser.getDecoder();
				
				decoder->failOnUnknown = false;
				decoder->checkSupport(metadata);
				decoder->decodeRaw();
				decoder->decodeMetaData(metadata);
				
				rawspeed::RawImage raw = decoder->mRaw;
				raw->scaleBlackWhite();
				int components_per_pixel = raw->getCpp();
				rawspeed::RawImageType type = raw->getDataType();
				bool is_cfa = raw->isCFA;

				unsigned char* data = raw->getData(0,0);
				int width = raw->dim.x;
				int height = raw->dim.y;
				int pitch_in_bytes = raw->pitch;
				size = glm::vec2(width, height);
				
				uint8_t *glData = (uint8_t *)malloc(width * height * sizeof(uint16_t));
				for (int y = 0; y < height; ++y)
				{
					uint8_t *line_src = &data[y * pitch_in_bytes];
					uint8_t *line_dst = &glData[y * sizeof(uint16_t) * width];
					memcpy(line_dst, line_src, sizeof(uint16_t) * width);
				}

				glGenTextures(1, &this->textureId);
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_RECTANGLE, this->textureId);
				glTexImage2D(GL_TEXTURE_RECTANGLE, 0, GL_R16, width, height, 0, GL_RED, GL_UNSIGNED_SHORT, glData);

				free(glData);
				glData = nullptr;

			}
			catch (rawspeed::CameraMetadataException &e) 
			{
				// Reading metadata failed. e.what() will contain error message.
				std::cerr << "Error loading metadata: " << e.what() << std::endl;
			}
			catch (rawspeed::FileIOException &e)
			{
				std::cerr << "Error reading file: " << e.what() << std::endl;
			}
			catch (rawspeed::RawDecoderException &e)
			{
				std::cerr << "Error getting decoder: " << e.what() << std::endl;
			}

			
			 


			
			
			

			

			
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

		GLenum Texture::GetWrapS()  
		{
			return GL_CLAMP_TO_EDGE;
		}

		GLenum Texture::GetWrapT()  
		{
			return GL_CLAMP_TO_EDGE;
		}

		GLenum Texture::GetMinFilter() 
		{
			return GL_NEAREST;
		}

		GLenum Texture::GetMagFilter() 
		{
			return GL_NEAREST;
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

