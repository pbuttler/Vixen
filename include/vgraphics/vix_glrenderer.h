#ifndef VIX_GL_RENDERER_H
#define VIX_GL_RENDERER_H

#include <vix_platform.h>
#include <vix_renderer.h>
#include <vix_color.h>

namespace Vixen {

	class VIX_API GLRenderer : public IRenderer
	{
	public:

		void VShutDown()                        override;
		void VSetClearColor(const Color& c)     override;
		void VClearBuffer(ClearArgs args)       override;
	};

}


#endif