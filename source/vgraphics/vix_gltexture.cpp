#include <vix_gltexture.h>

namespace Vixen {

	//NOTE:
	//
	//	Clearly there are more internal formats, and the formats
	//  for images depend on their compression type, bits, etc.
	//  Eventually this should take all that into account
	//
	GLenum vixFIBmpToInternalFormat(FIBITMAP* bmp)
	{
		GLenum format = GL_NONE;

		size_t bpp = FreeImage_GetBPP(bmp);
		switch (bpp)
		{
		case 24:
			format = GL_RGB8;
			break;
		case 32:
			format = GL_RGBA8;
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
	GLenum vixFIBmpToFormat(FIBITMAP* bmp)
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

	GLTexture::GLTexture(GLenum target /* = GL_TEXTURE_2D */)
	{
		m_width = 0;
		m_height = 0;
	}

	GLTexture::GLTexture(const std::string& filePath, GLenum target /* = GL_TEXTURE_2D */)
	{
		m_width = 0;
		m_height = 0;

		if (!CheckError(InitFromFile(filePath))) {
			//Debug Log a error message for texture initialization
		}
	}

	GLTexture::~GLTexture()
	{
		//unload opengl generated texture
		glDeleteTextures(1, &m_id);
	}

	ErrCode GLTexture::InitFromFile(const std::string& filePath)
	{
		//pointer to image data
		VIX_FIBitmap* image = NULL;

		//try and load the buffer with data
		image = vixFILoadImage(filePath);
		if (!image)
			return ErrCode::ERR_IMAGE_LOAD_FAILURE;

		//store width and height
		m_width = image->width;
		m_height = image->height;

		//now that we have our image data, create opengl texture handle
		glGenTextures(1, &m_id);

		//bind opengl texture handle
		glBindTexture(m_target, m_id);

		//retrieve internal format
		GLenum internalFormat = vixFIBmpToInternalFormat(image->bitmap);
		//retrieve format
		GLenum format = vixFIBmpToFormat(image->bitmap);
		
		//hand opengl the image
		glTexImage2D(m_target, 0, internalFormat, image->width, image->height, 0, format, GL_UNSIGNED_BYTE, image->data);
		glGenerateMipmap(m_target);
		glTexParameteri(m_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		//cleanup image allocation
		if (image)
			delete image;

		return ErrCode::ERR_SUCCESS;
	}

}