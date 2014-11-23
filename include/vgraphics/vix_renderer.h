#ifndef VIX_RENDERER_H
#define VIX_RENDERER_H

namespace Vixen {

	class Color;
	class Sprite;
	class Texture;
	class Transform;
	class Font;


	enum class ClearArgs
	{
		COLOR_BUFFER,
		DEPTH_BUFFER,
		STENC_BUFFER,
		COLOR_DEPTH_BUFFER,
		COLOR_STENCIL_BUFFER,
		DEPTH_STENCIL_BUFFER,
		COLOR_DEPTH_STENCIL_BUFFER,
	};

	class VIX_API IRenderer
	{
	public:

		virtual void VShutDown() = 0;
		virtual void VSetClearColor(const Color& c) = 0;
		virtual void VClearBuffer(ClearArgs args) = 0;

	};

}

#endif