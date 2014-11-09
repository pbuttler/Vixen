#include <vix_quaternion.h>
#include <cassert>
#include <math.h>

namespace Vixen {

	const Quaternion Quaternion::Identity(1, 0, 0, 0);
	const Quaternion Quaternion::Zero(0, 0, 0, 0);

	float Quaternion::Norm() const
	{
		float w = m_w * m_w;
		float x = m_x * m_x;
		float y = m_y * m_y;
		float z = m_z * m_z;

		return w + x + y + z;
	}

	float Quaternion::Normalize()
	{
		float norm = Norm();
		float f = 1.0f / sqrt(norm);

		*this = (*this * f);

		//return the norm
		return norm;
	}

	float Quaternion::operator[] (const size_t i) const
	{
		assert(i < 4); //only 3 members

		return *(&m_x + i);
	}

	float& Quaternion::operator[] (const size_t i)
	{
		assert(i < 4); //only 3 members

		return *(&m_x + i);
	}

	Quaternion Quaternion::operator* (float scalar) const
	{
		float w = m_w * scalar;
		float x = m_x * scalar;
		float y = m_y * scalar;
		float z = m_z * scalar;

		return Quaternion(w, x, y, z);
	}

	Quaternion Quaternion::operator* (const Quaternion& rhs) const
	{
		float w = 0.0f;
		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;

		//calculate new w
		w = (rhs.m_w * m_w) - 
			(rhs.m_x * m_x) - 
			(rhs.m_y * m_y) - 
			(rhs.m_z * m_z);

		//calculate new x
		x = (rhs.m_w * m_x) +
			(rhs.m_x * m_w) -
			(rhs.m_y * m_z) +
			(rhs.m_z * m_y);

		//calculate new y
		y = (rhs.m_w * m_y) +
			(rhs.m_x * m_z) +
			(rhs.m_y * m_w) -
			(rhs.m_z * m_x);

		//calculate new z
		z = (rhs.m_w * m_z) -
			(rhs.m_x * m_y) +
			(rhs.m_y * m_x) +
			(rhs.m_z * m_w);

		return Quaternion(w, x, y, z);
	}
}