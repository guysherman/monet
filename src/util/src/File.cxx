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
#include <memory>
#include <string>
#include <fstream>
// C Standard Headers


// Boost Headers

// 3rd Party Headers

// GTK Headers


// Our Headers
#include "../include/util/File.h"

namespace monet
{
	namespace util
	{
		File::File() {}
		File::~File() {}

		File* File::instance = nullptr;

		File* File::GetInstance()
		{
			if (nullptr == instance)
			{
				instance = new File();
			}
			return instance;
		}

		std::string File::GetDataAsString(std::string filePath)
		{
			std::string result = "";
			std::ifstream is (filePath, std::ifstream::binary);
			if (is) 
			{
				// get length of file:
				is.seekg (0, is.end);
				int length = is.tellg();
				is.seekg (0, is.beg);

				result.reserve(length);
				result.resize(length, '\0');

				// read data as a block:
				is.read (&result[0],length);

				is.close();
			}

			return result;

		}
	}
}

