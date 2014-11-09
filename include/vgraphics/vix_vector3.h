#ifndef VIX_VECTOR3_H
#define VIX_VECTOR3_H

#include <vix_platform.h>	

namespace Vixen {

	class VIX_API Vector3
	{
	public:
		float m_x;
		float m_y;
		float m_z;
	public:
		inline Vector3(float x, float y, float z)
			: m_x(x), m_y(y), m_z(z)
		{

		}

		//constants
		static const Vector3 Zero;
		static const Vector3 One;
		static const Vector3 UnitX;
		static const Vector3 UnitY;
		static const Vector3 UnitZ;
		static const Vector3 Up;
		static const Vector3 Down;
		static const Vector3 Right;
		static const Vector3 Left;
		static const Vector3 Forward;
		static const Vector3 Backward;
	};
}

#endif