#ifndef VIX_PRIMITIVE_TRIANGLE_H
#define VIX_PRIMITIVE_TRIANGLE_H

#include <vix_platform.h>
#include <vix_gl.h>
#include <vix_glbuffers.h>
#include <vix_glcamera3d.h>
#include <vix_vertex_defs.h>

namespace Vixen {

	class VIX_API PrimitiveTriangle
	{
	public:
		PrimitiveTriangle();

		~PrimitiveTriangle();


		void Render(GLCamera3D* camera);

	private:
		VertexPosColorBuffer*  m_vBuffer;
		GLIndexBuffer*         m_iBuffer;

		/*UTILITY FUNCTIONS*/
		
		void init();

		/*STATIC CONSTANTS*/
		static const size_t VERTEX_COUNT = 3;
		static const size_t INDEX_COUNT = 3;
	};

}

#endif