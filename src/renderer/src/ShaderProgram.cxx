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
#include <string>
#include <iostream>
#include <vector>
// C Standard Headers


// Boost Headers

// 3rd Party Headers
#include <glm/glm.hpp>

// GTK Headers


// Our Headers
#include "../include/renderer/ShaderProgram.h"
#include <util/File.h>

namespace monet
{
    namespace renderer
	{
		ShaderProgram::ShaderProgram(std::string vsName, std::string fsName)
		{
			this->vertexShaderId = 0;
			this->fragmentShaderId = 0;
			this->programId = 0;
			
			auto file = monet::util::File::GetInstance();
			auto vsText = file->GetDataAsString(vsName);
			auto vsCstr = vsText.c_str();
			this->vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(this->vertexShaderId, 1, &vsCstr, nullptr);
			glCompileShader(this->vertexShaderId);

			auto fsText = file->GetDataAsString(fsName);
			auto fsCstr = fsText.c_str();
			this->fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(this->fragmentShaderId, 1, &fsCstr, nullptr);
			glCompileShader(this->fragmentShaderId);

			this->programId = glCreateProgram();
			glAttachShader(this->programId, this->fragmentShaderId);
			glAttachShader(this->programId, this->vertexShaderId);
			glLinkProgram(this->programId);

			GLint isLinked = 0;
			glGetProgramiv(this->programId, GL_LINK_STATUS, &isLinked);

			if (GL_FALSE == isLinked)
			{
				GLint maxLength = 0;
				glGetProgramiv(this->programId, GL_INFO_LOG_LENGTH, &maxLength);

				// The maxLength includes the NULL character
				std::vector<GLchar> infoLog(maxLength);
				glGetProgramInfoLog(this->programId, maxLength, &maxLength, &infoLog[0]);

				std::cerr << "Shader Error: " << &infoLog[0] << std::endl;
			}
			

			
		}

		ShaderProgram::~ShaderProgram()
		{
			glDeleteShader(this->fragmentShaderId);
			glDeleteShader(this->vertexShaderId);
			glDeleteProgram(this->programId);
		}

		GLuint ShaderProgram::GetProgramId()
		{
			return this->programId;
		}
	}
}

