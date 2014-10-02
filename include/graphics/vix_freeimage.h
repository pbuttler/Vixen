#ifndef VIX_FREEIMAGE_H
#define VIX_FREEIMAGE_H

#include <vix_platform.h>
#include <vix_gl.h>
#include <FreeImage.h>

namespace Vixen {

	namespace Graphics {

		VIX_API GLenum fibToInternalFormat(FIBITMAP* bmp);
		VIX_API GLenum fibToFormat(FIBITMAP* bmp);

	}
}

#endif