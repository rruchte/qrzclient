#ifndef QRZ_BIORENDERER_H
#define QRZ_BIORENDERER_H

#include "Renderer.h"

#include <iostream>
#include <string>
#include <vector>

namespace qrz::render
{
	/**
	 * @class BioRenderer
	 * @brief The BioRenderer class is a concrete class for rendering bios.
	 *
	 * This class is derived from the Renderer class and provides the implementation for rendering bios.
	 * It takes a vector of bios as input and prints each bio to the console.
	 */
	class BioRenderer : public Renderer<std::string>
	{
	public:
		/**
		 * @brief Render the bios to the console.
		 *
		 * This method takes a vector of bios as input and prints each bio to the console.
		 *
		 * @param bios The vector of bios to be rendered.
		 */
		void Render(const std::vector<std::string> &bios) override
		{
			for (const std::string bio: bios)
			{
				std::cout << bio << std::endl;
			}
		}
	};
}

#endif //QRZ_BIORENDERER_H
