/*
	The MIT License(MIT)

	Copyright(c) 2014 Matt Guerrette

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files(the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions :
	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
*/

#ifndef VIX_QUATERNION_H
#define VIX_QUATERNION_H

#include <vix_platform.h>
#include <vix_vector3.h>
#include <iostream>

namespace Vixen {

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

		inline Quaternion(float scalar, const Vector3& vector)
		{
			m_w = scalar;
			m_x = vector.m_x;
			m_y = vector.m_y;
			m_z = vector.m_z;
		}

		//static functions
		static float Dot(const Quaternion& q, const Quaternion& r);

		//member functions
		float Dot(const Quaternion& q) const;
		float Norm() const;
		void  Normalize();
		float Length() const;
		Quaternion Inverse() const;
		Quaternion Unit() const;

		//operator overloads
		inline Quaternion& operator= (const Quaternion& rhs)
		{
			m_w = rhs.m_w;
			m_x = rhs.m_x;
			m_y = rhs.m_y;
			m_z = rhs.m_z;

			return *this;
		}

		inline bool operator== (const Quaternion& rhs)
		{
			return	(m_w == rhs.m_w) &&
					(m_x == rhs.m_x) &&
					(m_y == rhs.m_y) &&
					(m_z == rhs.m_z);
		}

		inline bool operator!= (const Quaternion& rhs)
		{
			return !(*this == rhs);
		}

		float  operator[] (const size_t i) const;
		float& operator[] (const size_t i);
		Quaternion operator- (void) const;
		Quaternion operator+ (const Quaternion& rhs) const;
		Quaternion operator+ (float scalar) const;
		Quaternion operator- (const Quaternion& rhs) const;
		Quaternion operator- (float scalar) const;
		Quaternion operator* (const Quaternion& rhs) const;
		Quaternion operator* (float scalar) const;
		Quaternion& operator+= (float scalar);
		Quaternion& operator+= (const Quaternion& rhs);
		Quaternion& operator-= (float scalar);
		Quaternion& operator-= (const Quaternion& rhs);
		Quaternion& operator*= (float scalar);
		Quaternion& operator*= (const Quaternion& rhs);

		static const Quaternion Identity;
		static const Quaternion Zero;


		inline VIX_API friend UOStream& operator <<
			(UOStream& o, const Quaternion& q)
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