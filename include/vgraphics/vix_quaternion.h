#ifndef VIX_QUATERNION_H
#define VIX_QUATERNION_H

#include <vix_platform.h>
#include <iostream>

namespace Vixen {

	class Vector3;

	class VIX_API Quaternion
	{
	public:
		float m_w;
		float m_x;
		float m_y;
		float m_z;

	public:
		inline Quaternion(float w, float x, float y, float z)
			: m_w(w), m_x(x), m_y(y), m_z(z)
		{
		}

		inline Quaternion(const Vector3& vector, float scalar)
		{

		}

		inline Quaternion& operator= (const Quaternion& rhs)
		{
			m_w = rhs.m_w;
			m_x = rhs.m_x;
			m_y = rhs.m_y;
			m_z = rhs.m_z;

			return *this;
		}

		float Norm() const;
		float Normalize();

		
		float  operator[] (const size_t i) const;
		float& operator[] (const size_t i);
		Quaternion operator+ (const Quaternion& rhs) const;
		Quaternion operator- (const Quaternion& rhs) const;
		Quaternion operator* (const Quaternion& rhs) const;
		Quaternion operator* (float scalar) const;

		static const Quaternion Identity;
		static const Quaternion Zero;


		inline VIX_API friend std::ostream& operator <<
			(std::ostream& o, const Quaternion& q)
		{
			o << "Quaternion [ "
				<< "w:" << q.m_w << ", "
				<< "x:" << q.m_x << ", "
				<< "y:" << q.m_y << ", "
				<< "z:" << q.m_z << " ]";
			return o;
		}
	};

}

#endif