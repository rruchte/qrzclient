#ifndef QRZ_RENDERER_H
#define QRZ_RENDERER_H

#include <vector>

namespace qrz::render
{
	template<typename T>
	class Renderer
	{
	public:
		virtual void Render(const std::vector<T> &toRender);
		virtual ~Renderer() = default;
	};

	template<typename T> void Renderer<T>::Render(const std::vector<T> &toRender){}
}


#endif //QRZ_RENDERER_H
