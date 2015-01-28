#ifndef VIX_PRIMITIVE_TRIANGLE_H
#define VIX_PRIMITIVE_TRIANGLE_H

#include <vix_platform.h>
#include <vix_gl.h>
#include <vix_glbuffers.h>
#include <vix_glcamera3d.h>
#include <vix_glshaderprogram.h>
#include <vix_vertex_defs.h>

namespace Vixen {

	class VIX_API PrimitiveTriangle
	{
	public:
		PrimitiveTriangle();

		~PrimitiveTriangle();

		void Rotate(float dt);

		void SetPosition(float x, float y, float z);

		void Render(GLCamera3D* camera);

	private:
		Vec3                   m_position;
		GLShaderProgram*       m_program;
		VertPosColBuffer*      m_vBuffer;
		GLIndexBuffer*         m_iBuffer;
		float                  m_rotation;

		/*UTILITY FUNCTIONS*/
		
		void init_shader_program();

		/*apply shader transform*/
		void applyTransform(GLCamera3D* camera);

		/*STATIC CONSTANTS*/
		static const size_t VERTEX_COUNT = 3;
		static const size_t INDEX_COUNT = 3;
	};

}

#endif