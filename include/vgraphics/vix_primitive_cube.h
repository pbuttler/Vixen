#ifndef VIX_PRIMITIVE_CUBE_H
#define VIX_PRIMITIVE_CUBE_H

#include <vix_platform.h>
#include <vix_gl.h>
#include <vix_glbuffers.h>
#include <vix_glcamera3d.h>
#include <vix_glshaderprogram.h>
#include <vix_vertex_defs.h>

namespace Vixen {

	class VIX_API PrimitiveCube
	{
	public:
		PrimitiveCube();

		~PrimitiveCube();

		void RotateX(float dt);
		void RotateY(float dt);
		void RotateZ(float dt);

		void SetPosition(float x, float y, float z);

		void Render(GLCamera3D* camera);

	private:
		Vec3                   m_position;
		GLShaderProgram*       m_program;
		VertPosColBuffer*      m_vBuffer;
		GLIndexBuffer*         m_iBuffer;
		float                  m_rotationX;
		float                  m_rotationY;
		float                  m_rotationZ;

		/*UTILITY FUNCTIONS*/

		void init_shader_program();
		void init_color_vi_buffers();

		/*apply shader transform*/
		void applyTransform(GLCamera3D* camera);

		/*STATIC CONSTANTS*/

		static const size_t COLOR_VERT_COUNT = 8;
		static const size_t COLOR_INDEX_COUNT = 36;
	};

}

#endif
