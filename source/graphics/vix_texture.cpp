#include <vix_texture.h>
#include <vix_osutil.h>
#include <vix_freeimage.h>

namespace Vixen {

	namespace Graphics {

		Texture::Texture(GLenum target, const std::string& path)
			: m_width(0),
			  m_height(0)
		{
			const std::string ospath = Util::os_path(path);
			if (!init(target, ospath)) {
				//log out error message
			}
		}

		Texture::~Texture()
		{
			glDeleteTextures(1, &m_id);
		}

		bool Texture::init(GLenum target, const std::string& path)
		{
			m_target   = target;
			m_filename = path;

			//image format
			FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;

			//pointer to image
			FIBITMAP* bmp = nullptr;
			//pointer to image data
			BYTE* bits = nullptr;
			BYTE* glbits = nullptr;

			//check file signature to deduce format
			fif = FreeImage_GetFileType(path.c_str(), 0);
			//if still unknown guess format from extension
			if (fif == FIF_UNKNOWN)
				fif = FreeImage_GetFIFFromFilename(path.c_str());
			//if still unknown, return fail
			if (fif == FIF_UNKNOWN)
				return false;
			

			//check that we have reading capabilities
			if (FreeImage_FIFSupportsReading(fif))
				bmp = FreeImage_Load(fif, path.c_str());
			//if failed, return
			if (!bmp)
				return false;

			//retrieve image data
			bits = FreeImage_GetBits(bmp);
			//get image width and height
			m_width = FreeImage_GetWidth(bmp);
			m_height = FreeImage_GetHeight(bmp);
			if (!bits || m_width == 0 || m_height == 0)
				return false;

			//generate OpenGL id
			glGenTextures(1, &m_id);
			//bind texture
			glBindTexture(m_target, m_id);
			glTexImage2D(m_target,
				         0, 
						 fibToInternalFormat(bmp), 
						 m_width, m_height, 
						 0, 
						 fibToFormat(bmp), 
						 GL_UNSIGNED_BYTE, 
						 bmp);
			glGenerateMipmap(m_target);
			glGetTexLevelParameterfv(m_target, NULL, GL_TEXTURE_WIDTH, &m_width);	//get texture width
			glGetTexLevelParameterfv(m_target, NULL, GL_TEXTURE_HEIGHT, &m_height); //get texture height
			glTexParameterf(m_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //linear filtering
			glTexParameterf(m_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //linear filtering

			FreeImage_Unload(bmp);

			return true;
		}

		bool Texture::operator== (const Texture& other)
		{
			return (m_id == other.m_id);
		}

		bool Texture::operator!= (const Texture& other)
		{
			return !(*this == other);
		}

	}
}