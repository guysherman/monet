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


// C Standard Headers


// Boost Headers

// 3rd Party Headers

// GTK Headers


// Our Headers
#include "../include/renderer/DisplayRenderPass.h"
#include "../include/renderer/RenderPasses.h"
#include "../include/renderer/Geometry.h"
#include "../include/renderer/Texture.h"
#include "../include/renderer/ShaderProgram.h"
#include "../include/renderer/Renderer.h"
#include "../include/renderer/RenderPasses.h"



namespace monet
{
    namespace renderer
	{
		DisplayRenderPass::DisplayRenderPass() 
		{
			
			program = std::shared_ptr<ShaderProgram>(new ShaderProgram("assets/display_vs.glsl", "assets/display_fs.glsl"));
		}

		DisplayRenderPass::~DisplayRenderPass() {}

		void DisplayRenderPass::Execute(Renderer *renderer, std::shared_ptr<IRenderPass> previous)
		{

			auto tex = previous->GetOutputTexture();
			auto texture = tex.lock();
			if (texture != nullptr)
			{
				auto size = texture->GetSize();
				//auto size = glm::vec2(6030, 4028);
				auto geometry = std::shared_ptr<Geometry>(new Geometry(size));
				//renderer->BindDefaultFrameBuffer();
				
				renderer->BindShaderProgram(program->GetProgramId());
				renderer->MapTextureUnit(0, "basic_texture", program->GetProgramId());
				renderer->SetMvpMatrix("matrix", program->GetProgramId(), size.x / size.y);
				renderer->BindTexture(tex);
				renderer->RenderGeometry(std::weak_ptr<Geometry>(geometry));
			}
			
		}

		RenderPass DisplayRenderPass::GetType()
		{
			return RenderPass::DISPLAY;
		}

		std::weak_ptr<Texture> DisplayRenderPass::GetOutputTexture()
		{
			return std::weak_ptr<Texture>(std::shared_ptr<Texture>(nullptr));
		}
	}
}

