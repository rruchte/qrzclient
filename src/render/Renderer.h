#ifndef QRZ_RENDERER_H
#define QRZ_RENDERER_H

#include <vector>

namespace qrz::render
{
	/**
	 * @class Renderer
	 * @brief The Renderer class is a base class for rendering objects of type T.
	 *
	 * This class provides a common interface for rendering objects of type T.
	 * It is an abstract class meant to be derived from and customized for specific types of rendering.
	 *
	 * @tparam T The type of objects to be rendered.
	 */
	template<typename T>
	class Renderer
	{
	public:
		/**
		 * @brief Virtual method for rendering objects.
		 *
		 * This method is responsible for rendering objects of type T. It takes a vector of objects to be rendered as input.
		 * Derived classes must implement this method to provide custom rendering functionality based on the type of objects being rendered.
		 *
		 * @tparam T The type of objects to be rendered.
		 * @param toRender A reference to a vector of objects to be rendered.
		 */
		virtual void Render(const std::vector<T> &toRender);
		virtual ~Renderer() = default;
	};

	template<typename T> void Renderer<T>::Render(const std::vector<T> &toRender){}
}


#endif //QRZ_RENDERER_H
