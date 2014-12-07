#include <vix_glbuffers.h>

namespace Vixen {

	GLBuffer::GLBuffer(GLenum target,
					   size_t stride,
					   size_t count,
		               const GLvoid* data)
					   : m_target(target),
					     m_size(stride * count),
						 m_count(count),
						 m_stride(stride)
	{
		glGenBuffers(1, &m_buffer);
		bind();
		glBufferData(m_target, m_size, data, GL_STATIC_DRAW);
		unbind();
	}

	void GLBuffer::set(size_t offset, size_t stride, size_t count, const GLvoid* data)
	{
		bind();
		glBufferSubData(m_target, offset, stride * count, data);
		unbind();
	}

	GLBuffer::~GLBuffer()
	{
		/*delete buffer*/
		glDeleteBuffers(1, &m_buffer);
	}

	void GLBuffer::bind()
	{
		/*bind buffer to opengl*/
		glBindBuffer(m_target, m_buffer);
	}

	void GLBuffer::unbind()
	{
		/*unbind buffer from opengl*/
		glBindBuffer(m_target, NULL);
	}
}