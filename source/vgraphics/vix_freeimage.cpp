#include <vix_freeimage.h>

namespace Vixen {


	//NOTE:
	//
	//	Clearly there are more internal formats, and the formats
	//  for images depend on their compression type, bits, etc.
	//  Eventually this should take all that into account
	//
	GLenum fibToInternalFormat(FIBITMAP* bmp)
	{
		GLenum format = GL_NONE;

		size_t bpp = FreeImage_GetBPP(bmp);
		switch (bpp)
		{
		case 24:
			format = GL_RGB;
			break;
		case 32:
			format = GL_RGBA;
			break;
		}
			
		return format;
	}

	//NOTE:
	//
	//	Clearly there are more formats, and the formats
	//  for images depend on their compression type, bits, etc.
	//  Eventually this should take all that into account
	//
	GLenum fibToFormat(FIBITMAP* bmp)
	{
		GLenum format = GL_NONE;

		size_t bpp = FreeImage_GetBPP(bmp);
		switch (bpp)
		{
		case 24:
			format = GL_BGR;
			break;
		case 32:
			format = GL_BGRA;
			break;
		}

		return format;
	}

}