#ifndef VIX_TEXTURE_H
#define VIX_TEXTURE_H

#include <vix_platform.h>
#include <vix_gl.h>

namespace Vixen {

	class VIX_API Texture
	{
		GLuint  m_textureId;
		GLenum  m_target;
		GLenum  m_unit;
		size_t  m_width;
		size_t  m_height;

	public:
		Texture();

		~Texture();
	};

}

#endif