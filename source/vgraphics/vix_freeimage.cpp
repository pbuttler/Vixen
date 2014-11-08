#include <vix_freeimage.h>

namespace Vixen {

	VIX_FIBitmap* vixFILoadImage(const std::string& filePath)
	{
		VIX_FIBitmap* vix_bmp = new VIX_FIBitmap;
		vix_bmp->path = filePath;
		vix_bmp->name = getFileName(filePath);
		vix_bmp->format = FIF_UNKNOWN;
		vix_bmp->data = NULL;
		vix_bmp->bitmap = NULL;
		vix_bmp->width = 0;
		vix_bmp->height = 0;
		
		//Check file signature and deduce format
		vix_bmp->format = FreeImage_GetFileType(filePath.c_str());
		if (vix_bmp->format == FIF_UNKNOWN)
			vix_bmp->format = FreeImage_GetFIFFromFilename(filePath.c_str());
		//if still unknown, return NULL;
		if (vix_bmp->format == FIF_UNKNOWN)
			return NULL;

		//Check if FreeImage has reading capabilities
		if (FreeImage_FIFSupportsReading(vix_bmp->format)) {
			//read image into struct pointer
			vix_bmp->bitmap = FreeImage_Load(vix_bmp->format, filePath.c_str());
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