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


#include <vix_gltexture.h>
#include <vix_debugutil.h>

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
		m_target = target;
	}

	GLTexture::GLTexture(const UString& filePath, GLenum target /* = GL_TEXTURE_2D */)
	{
		m_width = 0;
		m_height = 0;
		m_target = target;

		ErrCode error = InitFromFile(filePath);
		if (CheckError(InitFromFile(filePath))) {
			DebugPrintF(VTEXT("Texture failed to initialize: %s\n"),
				ErrCodeString(error));
		}
	}

	GLTexture::~GLTexture()
	{
		//unload opengl generated texture
		glDeleteTextures(1, &m_id);
	}

	void GLTexture::Bind(GLenum unit)
	{
		m_unit = unit;
		glBindMultiTextureEXT(m_unit, m_target, m_id);
	}

	void GLTexture::Unbind()
	{
		glBindMultiTextureEXT(m_unit, m_target, NULL);
	}

	ErrCode GLTexture::InitFromFile(const UString& filePath)
	{
		//pointer to image data
		VIX_FIBitmap* image = NULL;

		/*set texture name*/
		m_name = getFileName(filePath);

		//try and load the buffer with data
		image = vixFILoadImage(filePath);
		if (!image)
			return ErrCode::ERR_IMAGE_LOAD_FAIL;

		//store width and height
		m_width = image->width;
		m_height = image->height;

		//now that we have our image data, create opengl texture handle
		glGenTextures(1, &m_id);
		m_uniqueID = m_id; //store gl texture id as unique id

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