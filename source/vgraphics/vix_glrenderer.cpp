/*
	The MIT License(MIT)

	Copyright(c) 2014 Matt Guerrette

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files(the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions :
	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
*/

#include <vix_glrenderer.h>
#include <vix_gl.h>
#include <vix_debugutil.h>
#include <FreeImage.h>

namespace Vixen {

	void GLRenderer::VSetClearColor(const Color& c)
	{
		//set clear color
		glClearColor(c.r, c.g, c.b, c.a);
	}

	ErrCode GLRenderer::VInit()
	{
		ErrCode error = ErrCode::ERR_SUCCESS;

		/*initialize glew*/
		GLenum glewErr = glewInit();
		if (glewErr != GLEW_OK) {
			DebugPrintF(VTEXT("Glew failed to initialize: %s\n%s\n"),
				glewGetErrorString(glewErr), 
				ErrCodeString(ErrCode::ERR_GLEW_INIT_FAIL));
			return ErrCode::ERR_GLEW_INIT_FAIL;
		}

		return error;
	}

	void GLRenderer::VClearBuffer(ClearArgs args)
	{
		switch (args)
		{
		case ClearArgs::COLOR_BUFFER:
			glClear(GL_COLOR_BUFFER_BIT);
			break;
		case ClearArgs::DEPTH_BUFFER:
			glClear(GL_DEPTH_BUFFER_BIT);
			break;
		case ClearArgs::STENC_BUFFER:
			glClear(GL_STENCIL_BUFFER_BIT);
			break;
		case ClearArgs::COLOR_DEPTH_BUFFER:
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			break;

		case ClearArgs::COLOR_STENCIL_BUFFER:
			glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
			break;

		case ClearArgs::DEPTH_STENCIL_BUFFER:
			glClear(GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
			break;

		case ClearArgs::COLOR_DEPTH_STENCIL_BUFFER:
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
			break;
		}
	}

	void GLRenderer::VShutDown()
	{
		
	}


}