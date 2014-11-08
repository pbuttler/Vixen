#ifndef VIX_VECTOR2_H
#define VIX_VECTOR2_H

#include <vix_platform.h>

namespace Vixen {

	class VIX_API Vector2
	{
		float m_x;
		float m_y;
	public:
		inline Vector2()
			: m_x(0), m_y(0)
		{

		}

		inline Vector2(float x, float y)
			: m_x(x), m_y(y)
		{

		}

		//constants
		static const Vector2 Zero;
		static const Vector2 Unit;
		static const Vector2 UnitX;
		static const Vector2 UnitY;
	};

}

#endif