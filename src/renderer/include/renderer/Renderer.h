#ifndef _RENDERER_H_
#define _RENDERER_H_

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
#include <memory>
#include <vector>

// C Standard Headers


// Boost Headers

// 3rd Party Headers
#include <glm/glm.hpp>

// GTK Headers


// Our Headers
#include "RenderPasses.h"


namespace monet
{
    namespace renderer
    {
        class Texture;
		class Geometry;
		class IRenderPass;
		
		class Renderer
        {
        public:
			Renderer();
            virtual ~Renderer();

            void Draw();
			void ResizeView(float width, float height);
			void SetImageAspectRatio(float aspect);

			void BindShaderProgram(GLuint programId);
			void SetMvpMatrix(std::string uniformName, GLuint programId, float imageViewAspectRatio);
			void BindTexture(std::weak_ptr<Texture> texture);
			void RenderGeometry(std::weak_ptr<Geometry> geometry);

			void AddRenderPass(RenderPass pass);
			void ClearProcessingPipeline();
			std::vector< std::weak_ptr<IRenderPass> > GetProcessingPipeline();
		private:
			glm::vec2 viewSize;
			float imageAspectRatio;

			glm::mat4 getMvp();
			std::vector< std::shared_ptr<IRenderPass> > processingPipeline;
        };
    }
}

#endif //_RENDERER_H_