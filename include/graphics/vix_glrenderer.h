#ifndef VIX_GL_RENDERER_H
#define VIX_GL_RENDERER_H

#include <vix_platform.h>
#include <vix_interfaces.h>



namespace Vixen {

	class Color;

	class GLRenderer : public IRenderer
	{
	public:

		void VSetClearColor(byte r, byte g, byte b, byte a) override;
		void VSwapBuffers() override;
	};

}


#endif