#ifndef VIX_QUATERNION_H
#define VIX_QUATERNION_H

#include <vix_platform.h>

namespace Vixen {

	class Vector3;

	class VIX_API Quaternion
	{
		float m_x;
		float m_y;
		float m_z;
		float m_w;

	public:
		inline Quaternion(float x, float y, float z, float w)
			: m_x(x), m_y(y), m_z(z), m_w(w)
		{
		}

		inline Quaternion(const Vector3& vector, float scalar)
		{

		}


		static const Quaternion Identity;
		static const Quaternion Zero;
	};

}

#endif