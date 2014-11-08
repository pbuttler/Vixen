#ifndef VIX_TEXTURE_H
#define VIX_TEXTURE_H

#include <vix_platform.h>
#include <vix_errglobals.h>
#include <vix_freeimage.h>

namespace Vixen {

	class VIX_API Texture
	{
	public:
		Texture();
		virtual ~Texture();

		virtual ErrCode InitFromFile(const std::string& filePath) = 0;

		size_t  getWidth();
		size_t  getHeight();
	protected:
		size_t  m_width;
		size_t  m_height;
	};
}

#endif