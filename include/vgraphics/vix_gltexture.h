#ifndef VIX_GL_TEXTURE_H
#define VIX_GL_TEXTURE_H

#include <vix_platform.h>
#include <vix_gl.h>
#include <vix_texture.h>

namespace Vixen {

	VIX_API GLenum vixFIBmpToInternalFormat(FIBITMAP* bmp);
	VIX_API GLenum vixFIBmpToFormat(FIBITMAP* bmp);

	class VIX_API GLTexture : public Texture
	{
		GLuint m_id;
		GLenum m_target;
		GLenum m_unit;

	public:
		GLTexture(GLenum target = GL_TEXTURE_2D);
		GLTexture(const std::string& filePath, GLenum target = GL_TEXTURE_2D);

		~GLTexture();

		ErrCode InitFromFile(const std::string& filePath);
	};
}

#endif