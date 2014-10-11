#ifndef VIX_VEC2_H
#define VIX_VEC2_H

#include <vix_platform.h>

#include <cassert>
#include <cmath>

namespace Vixen {

	class VIX_API Vec2F
	{
	public:
		float x;
		float y;

	public:
		inline Vec2F(void)
			: x(0.0f), y(0.0f)
		{
		}
			
		inline Vec2F(float _x, float _y)
			: x(_x), y(_y)
		{
		}

		//////////////////////////////////////////////////////////////////////////
		inline bool operator == (const Vec2F& rhs) const
		{
			return (x == rhs.x && y == rhs.y);
		}
		//////////////////////////////////////////////////////////////////////////
		inline bool operator != (const Vec2F& rhs) const
		{
			return (x != rhs.x || y != rhs.y);
		}
		//////////////////////////////////////////////////////////////////////////
		inline Vec2F operator + (const Vec2F& rhs) const
		{
			return Vec2F(x + rhs.x, y + rhs.y);
		}
		//////////////////////////////////////////////////////////////////////////
		inline Vec2F operator - (const Vec2F& rhs) const
		{
			return Vec2F(x - rhs.x, y - rhs.y);
		}
		//////////////////////////////////////////////////////////////////////////
		inline Vec2F operator * (const Vec2F& rhs) const
		{
			return Vec2F(x * rhs.x, y * rhs.y);
		}
		//////////////////////////////////////////////////////////////////////////
		inline Vec2F operator * (const float scalar) const
		{
			return Vec2F(x * scalar, y * scalar);
		}
		//////////////////////////////////////////////////////////////////////////
		inline Vec2F operator / (const Vec2F& rhs) const
		{
			return Vec2F(x / rhs.x, y / rhs.y);
		}
		//////////////////////////////////////////////////////////////////////////
		inline Vec2F operator / (const float scalar) const
		{
			assert(scalar != 0.0f);
			float invScalar = 1.0f / scalar;
			return Vec2F(x * invScalar, y * invScalar);
		}
		//////////////////////////////////////////////////////////////////////////
		inline Vec2F& operator += (const Vec2F& rhs)
		{
			x += rhs.x;
			y += rhs.y;
			return *this;
		}
		//////////////////////////////////////////////////////////////////////////
		inline Vec2F& operator += (const float scalar)
		{
			x += scalar;
			y += scalar;
			return *this;
		}
		//////////////////////////////////////////////////////////////////////////
		inline Vec2F& operator -= (const Vec2F& rhs)
		{
			x -= rhs.x;
			y -= rhs.y;
			return *this;
		}
		//////////////////////////////////////////////////////////////////////////
		inline Vec2F& operator -= (const float scalar)
		{
			x -= scalar;
			y -= scalar;
			return *this;
		}
		//////////////////////////////////////////////////////////////////////////
		inline Vec2F& operator *= (const Vec2F& rhs)
		{
			x *= rhs.x;
			y *= rhs.y;
			return *this;
		}
		//////////////////////////////////////////////////////////////////////////
		inline Vec2F& operator *= (const float scalar)
		{
			x *= scalar;
			y *= scalar;
			return *this;
		}
		//////////////////////////////////////////////////////////////////////////
		inline Vec2F& operator /= (const Vec2F& rhs)
		{
			x /= rhs.x;
			y /= rhs.y;
			return *this;
		}
		//////////////////////////////////////////////////////////////////////////
		inline Vec2F& operator /= (const float scalar)
		{
			assert(scalar != 0.0f);
			float invScalar = 1.0f / scalar;
			x *= invScalar;
			y *= invScalar;
			return *this;
		}
		//////////////////////////////////////////////////////////////////////////
		inline friend Vec2F operator * (const float scalar, const Vec2F& rhs)
		{
			return Vec2F(scalar * rhs.x, scalar * rhs.y);
		}
		//////////////////////////////////////////////////////////////////////////
		inline friend Vec2F operator / (const float scalar, const Vec2F& rhs)
		{
			return Vec2F(scalar / rhs.x, scalar / rhs.y);
		}
		//////////////////////////////////////////////////////////////////////////
		inline float Length() const
		{
			return sqrt(x * x + y * y);
		}
		//////////////////////////////////////////////////////////////////////////
		inline float LengthSquared() const
		{
			return x * x + y * y;
		}
		//////////////////////////////////////////////////////////////////////////
		inline float Distance(const Vec2F& rhs) const
		{
			return (*this - rhs).Length();
		}
		//////////////////////////////////////////////////////////////////////////
		inline float DistSquared(const Vec2F& rhs) const
		{
			return (*this - rhs).LengthSquared();
		}
		//////////////////////////////////////////////////////////////////////////
		inline float Dot(const Vec2F& rhs) const
		{
			return x * rhs.x + y * rhs.y;
		}
		//////////////////////////////////////////////////////////////////////////
		inline float normalise(void)
		{
			float length = sqrt(x * x + y * y);
			if (length > 0.0f)
			{
				float lenInv = 1.0f / length;
				x *= lenInv;
				y *= lenInv;
			}
			return length;
		}
		//////////////////////////////////////////////////////////////////////////
		inline Vec2F Normalize(void) const
		{
			Vec2F ret = *this;
			ret.normalise();
			return ret;
		}
		
		static inline float Distance(Vec2F value1, Vec2F value2)
		{
			float v1 = value1.x - value2.x;
			float v2 = value1.y - value2.y;
			return sqrt((v1 * v1) + (v2 * v2));
		}

		//////////////////////////////////////////////////////////////////////////
		// STATIC CONSTANTS
		//////////////////////////////////////////////////////////////////////////
		static const Vec2F ZERO;
		static const Vec2F UNIT_X;
		static const Vec2F UNIT_Y;
		static const Vec2F NEG_UNIT_X;
		static const Vec2F NEG_UNIT_Y;
		static const Vec2F UNIT_SCALE;
	};
	
}

#endif