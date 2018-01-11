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
#include <glm/glm.hpp>



// GTK Headers


// Our Headers
#include "../include/renderer/DemosaicRenderPass.h"
#include "../include/renderer/Geometry.h"
#include "../include/renderer/Texture.h"
#include "../include/renderer/ShaderProgram.h"
#include "../include/renderer/Renderer.h"
#include "../include/renderer/RenderPasses.h"

namespace monet
{
    namespace renderer
	{
		DemosaicRenderPass::DemosaicRenderPass(DemosaicRenderPassConfig *config)
		{
			std::cout << "Creating DemosaicRenderPass for file: " << config->RawFilePath << std::endl;

			texture = std::shared_ptr<Texture>(new Texture(config->RawFilePath));
			geometry = std::shared_ptr<Geometry>(new Geometry(texture->GetSize()));
			program = std::shared_ptr<ShaderProgram>(new ShaderProgram());
		}

		DemosaicRenderPass::~DemosaicRenderPass() {}

		void DemosaicRenderPass::Execute(Renderer *renderer)
		{
			auto size = texture->GetSize();
			renderer->BindShaderProgram(program->GetProgramId());
			renderer->SetMvpMatrix("matrix", program->GetProgramId(), size.x / size.y);
			renderer->BindTexture(std::weak_ptr<Texture>(texture));
			renderer->RenderGeometry(std::weak_ptr<Geometry>(geometry));
		}

		RenderPass DemosaicRenderPass::GetType()
		{
			return RenderPass::DEMOSAIC;
		}
	}
}

