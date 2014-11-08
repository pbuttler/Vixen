#ifndef VIX_FREEIMAGE_H
#define VIX_FREEIMAGE_H

#include <vix_platform.h>
#include <vix_stringutil.h>
#include <vix_file.h>
#include <FreeImage.h>

namespace Vixen {

	struct VIX_FIBitmap
	{
		FIBITMAP*         bitmap;
		FREE_IMAGE_FORMAT format;
		byte*	          data;
		size_t            width;
		size_t            height;

		~VIX_FIBitmap()
		{
			if (bitmap)
				FreeImage_Unload(bitmap);
		}
	};

	VIX_API VIX_FIBitmap* vixFILoadImage(const std::string& filePath);
}

#endif