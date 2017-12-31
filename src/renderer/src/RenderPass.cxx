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
#include <string>
#include <iostream>
// C Standard Headers


// Boost Headers

// 3rd Party Headers
#include <glm/glm.hpp>

// GTK Headers


// Our Headers
#include "../include/renderer/RenderPass.h"
#include <util/File.h>

namespace monet
{
    namespace renderer
	{
		RenderPass::RenderPass()
		{
			this->vertexShaderId = 0;
			this->fragmentShaderId = 0;
			this->programId = 0;
			
			auto file = monet::util::File::GetInstance();
			auto vsText = file->GetDataAsString("assets/basic_vs.glsl");
			auto vsCstr = vsText.c_str();
			this->vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(this->vertexShaderId, 1, &vsCstr, nullptr);
			glCompileShader(this->vertexShaderId);

			auto fsText = file->GetDataAsString("assets/basic_fs.glsl");
			auto fsCstr = fsText.c_str();
			this->fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(this->fragmentShaderId, 1, &fsCstr, nullptr);
			glCompileShader(this->fragmentShaderId);

			this->programId = glCreateProgram();
			glAttachShader(this->programId, this->fragmentShaderId);
			glAttachShader(this->programId, this->vertexShaderId);
			glLinkProgram(this->programId);
		}

		RenderPass::~RenderPass()
		{
			glDeleteShader(this->fragmentShaderId);
			glDeleteShader(this->vertexShaderId);
			glDeleteProgram(this->programId);
		}

		GLuint RenderPass::GetProgramId()
		{
			return this->programId;
		}
	}
}

