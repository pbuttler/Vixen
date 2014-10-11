#include <vix_glrenderer.h>
#include <vix_gl.h>

namespace Vixen {

	void GLRenderer::VSetClearColor(byte r, byte g, byte b, byte a)
	{
		//set clear color
		glClearColor(r, g, b, a);
	}

	void GLRenderer::VSwapBuffers()
	{
		//NOTE:
		//  our opengl system assumes that we are using SDL,
		//  this could very well change in the future though
			
	}
}