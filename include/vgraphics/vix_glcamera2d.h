#ifndef VIX_GLCAMERA2D_H
#define VIX_GLCAMERA2D_H

#include <vix_platform.h>
#include <vix_glm.h>

namespace Vixen {
	
	/*
	*	Camera2D class
	*
	*   Describes an ORTHOGRAPHIC 2D camera
	*/
	class VIX_API GLCamera2D
	{
	public:
		GLCamera2D(float L,
			       float R,
				   float T,
				   float B);
		
		/*return projection*/
		const Mat4&  Projection();

		/*return view*/
		const Mat4&  View();

		/*update bounds*/
		void SetBounds(float L,
					   float R,
					   float T,
					   float B);

	private:
		Mat4  m_projection;
		Mat4  m_view;
		float m_left;
		float m_right;
		float m_top;
		float m_bottom;
	};
}

#endif