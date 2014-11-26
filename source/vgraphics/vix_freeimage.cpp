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

#include <vix_freeimage.h>

namespace Vixen {

	VIX_FIBitmap* vixFILoadImage(const UString& filePath)
	{
		VIX_FIBitmap* vix_bmp = new VIX_FIBitmap;
		vix_bmp->path = filePath;
		vix_bmp->name = getFileName(filePath);
		vix_bmp->format = FIF_UNKNOWN;
		vix_bmp->data = NULL;
		vix_bmp->bitmap = NULL;
		vix_bmp->width = 0;
		vix_bmp->height = 0;

		/*Here we must */
		
		//Check file signature and deduce format
#ifdef UNICODE
		vix_bmp->format = FreeImage_GetFileTypeU(filePath.c_str());
#else
		vix_bmp->format = FreeImage_GetFileType(filePath.c_str());
#endif
		if (vix_bmp->format == FIF_UNKNOWN) {
#ifdef UNICODE
			vix_bmp->format = FreeImage_GetFIFFromFilenameU(filePath.c_str());
#else
			vix_bmp->format = FreeImage_GetFIFFromFilename(filePath.c_str());
#endif
		}
			
		//if still unknown, return NULL;
		if (vix_bmp->format == FIF_UNKNOWN)
			return NULL;

		//Check if FreeImage has reading capabilities
		if (FreeImage_FIFSupportsReading(vix_bmp->format)) {
#ifdef UNICODE
			//read image into struct pointer
			vix_bmp->bitmap = FreeImage_LoadU(vix_bmp->format, filePath.c_str());
#else
			vix_bmp->bitmap = FreeImage_Load(vix_bmp->format, filePath.c_str());
#endif
		}

		//If image failed to load, return NULL
		if (!vix_bmp->bitmap)
			return NULL;

		//Retrieve image data
		vix_bmp->data = FreeImage_GetBits(vix_bmp->bitmap);
		//Retrieve image width
		vix_bmp->width = FreeImage_GetWidth(vix_bmp->bitmap);
		//Retrieve image height
		vix_bmp->height = FreeImage_GetHeight(vix_bmp->bitmap);
		if (vix_bmp->data == 0 || vix_bmp->width == 0 || vix_bmp->height == 0)
			return NULL;

		//return bitmap
		return vix_bmp;
	}

}