#ifndef VIX_PRIMITIVE_SPHERE
#define VIX_PRIMITIVE_SPHERE

#include <vix_platform.h>
#include <vix_gl.h>
#include <vix_glbuffers.h>
#include <vix_glcamera3d.h>
#include <vix_glshaderprogram.h>
#include <vix_vertex_defs.h>
#include <vix_color.h>
#include <vector>

namespace Vixen {

	class VIX_API PrimitiveSphere
	{
	public:
		PrimitiveSphere(void);
		PrimitiveSphere(float radius, float subdivisions, Color c);

		~PrimitiveSphere();

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
		float                  m_radius;
		float                  m_subdivisions;
		Color                  m_color;
		

		/*UTILITY FUNCTIONS*/

		void init_shader_program();
		void init_color_vi_buffers();

		/*apply shader transform*/
		void applyTransform(GLCamera3D* camera);

		/*STATIC CONSTANTS*/

		static const size_t RINGS = 24;
		static const size_t SECTORS = 48;
		static const size_t SUBDIVISIONS = 10;
		static const size_t SPHERE_INDEX_COUNT = 60;
		static const size_t SPHERE_VERTEX_COUNT = 12;
	};

}

#endif