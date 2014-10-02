#ifndef VIX_FREEIMAGE_H
#define VIX_FREEIMAGE_H

#include <vix_platform.h>
#include <vix_gl.h>
#include <FreeImage.h>

namespace Vixen {

	namespace Graphics {

		GLenum fibToInternalFormat(FIBITMAP* bmp);
		GLenum fibToFormat(FIBITMAP* bmp);

	}
}

#endif