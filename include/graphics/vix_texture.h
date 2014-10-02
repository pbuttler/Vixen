#ifndef VIX_TEXTURE_H
#define VIX_TEXTURE_H

#include <vix_platform.h>
#include <vix_interfaces.h>
#include <vix_gl.h>
#include <vix_stringutil.h>

namespace Vixen {

	namespace Graphics {

		class VIX_API Texture
		{
			GLuint		m_id;
			GLenum		m_target;
			GLenum		m_unit;
			float		m_width;
			float		m_height;
			std::string m_filename;

		public:
			Texture(GLenum target, const std::string& path);

			~Texture(void);

			bool operator== (const Texture& other);
			bool operator!= (const Texture& other);

		private:
			bool init(GLenum target, const std::string& path);
		};

	}
}

#endif