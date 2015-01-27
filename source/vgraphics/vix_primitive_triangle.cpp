#include <vix_primitive_triangle.h>
#include <array>

namespace Vixen {

	PrimitiveTriangle::PrimitiveTriangle()
	{
		m_vBuffer = new VertexPosColorBuffer(VERTEX_COUNT);
		m_iBuffer = new GLIndexBuffer(INDEX_COUNT);

		const std::array<unsigned short, INDEX_COUNT> temp =
		{
			0, 1, 2
		};
		m_iBuffer->set(0, INDEX_COUNT, temp.data());

	}

	PrimitiveTriangle::~PrimitiveTriangle()
	{
		delete m_vBuffer;
		delete m_iBuffer;
	}

	void PrimitiveTriangle::init()
	{

	}

	void PrimitiveTriangle::Render(GLCamera3D* camera)
	{
		m_vBuffer->bind();
		m_iBuffer->bind();

		m_vBuffer->unbind();
		m_iBuffer->unbind();
	}

}