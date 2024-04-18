#ifndef QRZ_BIORENDERER_H
#define QRZ_BIORENDERER_H

#include "Renderer.h"

#include <iostream>
#include <string>
#include <vector>

namespace qrz
{
	namespace render
	{
		class BioRenderer : public Renderer<std::string>
		{
		public:
			void Render(const std::vector<std::string> &bios) override
			{
				for (const std::string bio: bios)
				{
					std::cout << bio << std::endl;
				}
			}
		};
	}
}

#endif //QRZ_BIORENDERER_H
