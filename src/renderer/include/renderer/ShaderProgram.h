#ifndef _SHADERPROGRAM_H_
#define _SHADERPROGRAM_H_

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

// C Standard Headers


// Boost Headers

// 3rd Party Headers

// GTK Headers


// Our Headers

namespace monet
{
    namespace renderer
	{
		class ShaderProgram
		{
		public:
			ShaderProgram(std::string vsName, std::string fsName);
			virtual ~ShaderProgram();

			GLuint GetProgramId();
		private:
			GLuint programId;
			GLuint vertexShaderId;
			GLuint fragmentShaderId;
			
		};
	}
}

#endif //_SHADERPROGRAM_H_