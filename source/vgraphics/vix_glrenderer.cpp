#include <vix_glrenderer.h>
#include <vix_gl.h>

namespace Vixen {

	void GLRenderer::VSetClearColor(const Color& c)
	{
		//set clear color
		glClearColor(c.r, c.g, c.b, c.a);
	}

	void GLRenderer::VShutDown()
	{

	}


}