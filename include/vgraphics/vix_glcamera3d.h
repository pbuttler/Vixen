#ifndef VIX_GLCAMERA3D_H
#define VIX_GLCAMERA3D_H

#include <vix_platform.h>
#include <vix_glm.h>

namespace Vixen {

	enum class C3D_DIRECTION
	{
		UP,
		DOWN,
		LEFT,
		RIGHT,
		FORWARD,
		BACKWARD
	};


	class VIX_API GLCamera3D
	{
	public:
		GLCamera3D();

		/*Get Projection Matrix*/
		const Mat4& Projection() const;

		/*Get View Matrix*/
		const Mat4& View() const;

		/*Set Perspective Projection*/
		void SetPerspective(float aspect, float fov, float znear, float zfar);

		/*Set View Lens*/
		void SetView(const Vec3& pos, const Vec3& target, const Vec3& up);

		/*Move Camera*/
		void Move(C3D_DIRECTION cam_dir);

		/*Update Camera*/
		void Update(float dt);

	private:
		Mat4	m_projection;
		Mat4	m_view;
		Vec3    m_position;
		Vec3    m_target;
		Vec3    m_up;
		float   m_aspect;
		float   m_fov;
		float   m_znear;
		float   m_zfar;
	};

}

#endif