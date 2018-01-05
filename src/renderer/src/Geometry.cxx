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
#include  <GL/glew.h>

// C++ Standard Headers


// C Standard Headers


// Boost Headers

// 3rd Party Headers

// GTK Headers


// Our Headers
#include "../include/renderer/Geometry.h"

namespace monet
{
    namespace renderer
	{
		Geometry::Geometry()
		{
			GLfloat positions[8] ={ 0.0f,	0.0f,
									0.0f,   1.0f,
									1.0f, 	1.0f,
									1.0f,   0.0f };

			GLfloat tcs[8] 		= { 0.0f, 0.0f,
									0.0f, 1.0f,
									1.0f, 1.0f,
									1.0f, 0.0f };

			GLuint indices[6]		= { 0, 1, 2, 0, 2, 3 };

			numElements = 6;

			
			glGenBuffers( 1, &this->positionBufferId );
			glBindBuffer( GL_ARRAY_BUFFER, this->positionBufferId );
			glBufferData( GL_ARRAY_BUFFER, 8 * sizeof( GLfloat ), positions, GL_STATIC_DRAW );

			glGenBuffers( 1, &this->texCoordBufferId );
			glBindBuffer( GL_ARRAY_BUFFER, this->texCoordBufferId );
			glBufferData( GL_ARRAY_BUFFER, 8 * sizeof( GLfloat ), tcs, GL_STATIC_DRAW );

			glGenBuffers( 1, &this->indexBufferId );
			glBindBuffer( GL_ARRAY_BUFFER, this->indexBufferId );
			glBufferData( GL_ARRAY_BUFFER, 6 * sizeof( GLuint ), indices, GL_STATIC_DRAW );

			glGenVertexArrays( 1, &this->vaoId );
			glBindVertexArray( this->vaoId );

			glEnableVertexAttribArray( 0 );
			glEnableVertexAttribArray( 1 );

			glBindBuffer(GL_ARRAY_BUFFER, this->positionBufferId);
			glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr );

			glBindBuffer(GL_ARRAY_BUFFER, this->texCoordBufferId);
			glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr );

			glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, this->indexBufferId );
		}

		Geometry::~Geometry()
		{
			glDeleteBuffers( 1, &this->positionBufferId );
			glDeleteBuffers( 1, &this->texCoordBufferId );
			glDeleteBuffers( 1, &this->indexBufferId );

			glDeleteVertexArrays( 1, &this->vaoId );
		}

		GLuint Geometry::GetVaoId()
		{
			return this->vaoId;
		}

		GLuint Geometry::GetNumElements()
		{
			return numElements;
		}		
	}
}

