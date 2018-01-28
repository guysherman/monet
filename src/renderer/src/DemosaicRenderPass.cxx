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
#include <thread>

// C Standard Headers


// Boost Headers

// 3rd Party Headers
#include <glm/glm.hpp>

#include <RawSpeed-API.h>
#include <metadata/CameraMetadataException.h>
#include <io/FileIOException.h>

// GTK Headers


// Our Headers
#include "../include/renderer/DemosaicRenderPass.h"
#include "../include/renderer/Geometry.h"
#include "../include/renderer/Texture.h"
#include "../include/renderer/ShaderProgram.h"
#include "../include/renderer/Renderer.h"
#include "../include/renderer/RenderPasses.h"

int rawspeed_get_number_of_processor_cores()
{
	return std::thread::hardware_concurrency();
}

namespace monet
{
    namespace renderer
	{
		DemosaicRenderPass::DemosaicRenderPass(DemosaicRenderPassConfig *config)
		{
			std::cout << "Creating DemosaicRenderPass for file: " << config->RawFilePath << std::endl;

			try
			{
				rawspeed::CameraMetaData *metadata = new rawspeed::CameraMetaData("assets/cameras.xml");
				
				rawspeed::FileReader reader(config->RawFilePath.c_str());
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
				
				
				uint8_t *glData = (uint8_t *)malloc(width * height * sizeof(uint16_t));
				for (int y = 0; y < height; ++y)
				{
					uint8_t *line_src = &data[y * pitch_in_bytes];
					uint8_t *line_dst = &glData[y * sizeof(uint16_t) * width];
					memcpy(line_dst, line_src, sizeof(uint16_t) * width);
				}

				texture = std::shared_ptr<Texture>(new Texture(glData, width, height, GL_TEXTURE0, GL_TEXTURE_RECTANGLE, GL_R16, GL_RED, GL_UNSIGNED_SHORT, GL_NEAREST, GL_CLAMP_TO_EDGE));

				free(glData);
				glData = nullptr;

				std::vector<uint8_t> maskData;

				if (true == is_cfa) 
				{
					rawspeed::ColorFilterArray cfa = raw->cfa;
					int dcraw_filter = cfa.getDcrawFilter();
					int cfa_width = cfa.getSize().x;
					int cfa_height = cfa.getSize().y;
					
					for (int y = 0; y < cfa_height; ++y) 
					{
						for (int x = 0; x < cfa_width; ++x)
						{
							auto c = cfa.getColorAt(x, y);
							switch (c) 
							{
								case rawspeed::CFA_RED:
								{
									maskData.push_back(0xFF);
									maskData.push_back(0x00);
									maskData.push_back(0x00);
									maskData.push_back(0xFF);
									break;
								}
								case rawspeed::CFA_GREEN:
								{
									maskData.push_back(0xFF);
									maskData.push_back(0x00);
									maskData.push_back(0xFF);
									maskData.push_back(0x00);
									break;
								}
								case rawspeed::CFA_BLUE:
								{
									maskData.push_back(0xFF);
									maskData.push_back(0xFF);
									maskData.push_back(0x00);
									maskData.push_back(0x00);
									break;	
								}
								default:
								{
									maskData.push_back(0x00);
									maskData.push_back(0x00);
									maskData.push_back(0x00);
									maskData.push_back(0x00);
									break;	
								}
							}
						}
					}
				}



				mask = std::shared_ptr<Texture>(new Texture(&maskData[0], 2, 2, GL_TEXTURE1, GL_TEXTURE_2D, GL_RGBA, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, GL_NEAREST, GL_REPEAT));

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

			renderTexture = std::shared_ptr<Texture>(new Texture(
				nullptr,
				texture->GetSize().x,
				texture->GetSize().y,
				GL_TEXTURE0,
				GL_TEXTURE_RECTANGLE,
				GL_RGBA,
				GL_RGBA,
				GL_UNSIGNED_INT_8_8_8_8,
				GL_NEAREST,
				GL_CLAMP_TO_EDGE
			));
			geometry = std::shared_ptr<Geometry>(new Geometry(texture->GetSize()));
			program = std::shared_ptr<ShaderProgram>(new ShaderProgram("assets/basic_vs.glsl", "assets/basic_fs.glsl"));
		}

		DemosaicRenderPass::~DemosaicRenderPass() {}

		void DemosaicRenderPass::Execute(Renderer *renderer, std::shared_ptr<IRenderPass> previous)
		{
			GLuint frameBufferId;
			GLenum drawBuffer;

			GLint dfbo, rfbo;
			renderer->GetCurrentFboIds(&dfbo, &rfbo);
			auto size = texture->GetSize();
			renderer->BindShaderProgram(program->GetProgramId());
			renderer->BindRenderTexture(std::weak_ptr<Texture>(renderTexture), &frameBufferId, &drawBuffer);
			renderer->SetViewport(0, 0, size.x, size.y);
			renderer->MapTextureUnit(0, "basic_texture", program->GetProgramId());
			renderer->MapTextureUnit(1, "mask_texture", program->GetProgramId());
			renderer->SetMvpMatrixForRenderTexture("matrix", program->GetProgramId());
			renderer->BindTexture(std::weak_ptr<Texture>(texture));
			renderer->BindTexture(std::weak_ptr<Texture>(mask));
			renderer->RenderGeometry(std::weak_ptr<Geometry>(geometry));
			renderer->DeleteFrameBuffer(&frameBufferId);
			renderer->BindDefaultFrameBuffers(&dfbo, &rfbo);
			renderer->RestoreViewportToViewSize();
		}

		RenderPass DemosaicRenderPass::GetType()
		{
			return RenderPass::DEMOSAIC;
		}

		std::weak_ptr<Texture> DemosaicRenderPass::GetOutputTexture()
		{
			return std::weak_ptr<Texture>(renderTexture);
		}
	}
}

