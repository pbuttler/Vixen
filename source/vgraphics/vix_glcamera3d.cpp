#include <vix_glcamera3d.h>

namespace Vixen {

	GLCamera3D::GLCamera3D()
		: m_aspect(0.0f),
		  m_fov(0.0f),
		  m_znear(1.0f),
		  m_zfar(1000.0f),
		  m_position(0.0f),
		  m_target(0.0f, 0.0f, -1.0f),
		  m_up(0.0f, 1.0f, 0.0f)
	{
		
	}

	void GLCamera3D::SetPerspective(float aspect, float fov, float znear, float zfar)
	{
		/*should probably check for stupid fov ranges*/
		m_aspect = aspect;
		m_fov = fov;
		m_znear = znear;
		m_zfar = zfar;
		m_projection = glm::perspective(m_fov, m_aspect, m_znear, m_zfar);
	}

	void GLCamera3D::SetView(const Vec3& pos, const Vec3& target, const Vec3& up)
	{
		m_position = pos;
		m_target = target;
		m_up = up;

		m_view = glm::lookAt(m_position, m_target, m_up);
	}

	void GLCamera3D::Move(C3D_DIRECTION cam_dir)
	{
		switch (cam_dir)
		{
		case Vixen::C3D_DIRECTION::UP:
			break;
		case Vixen::C3D_DIRECTION::DOWN:
			break;
		case Vixen::C3D_DIRECTION::LEFT:
			break;
		case Vixen::C3D_DIRECTION::RIGHT:
			break;
		case Vixen::C3D_DIRECTION::FORWARD:
			break;
		case Vixen::C3D_DIRECTION::BACKWARD:
			break;
		default:
			break;
		}
	}

	const Mat4& GLCamera3D::Projection() const
	{
		return m_projection;
	}

	const Mat4& GLCamera3D::View() const
	{
		return m_view;
	}

}