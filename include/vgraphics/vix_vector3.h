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

#ifndef VIX_VECTOR3_H
#define VIX_VECTOR3_H

#include <vix_platform.h>
#include <vix_math.h>
#include <sstream>

namespace Vixen {

	class VIX_API Vector3
	{
	public:
		float x;
		float y;
		float z;
	public:

#ifdef ENABLE_NAN_DIAGNOSTICS
		inline void DiagnosticNanCheck() const
		{
			if(ContainsNaN()) {
				DebugPrintF("Vector contains NaN: %s", )
			}
		}
#else
		inline void DiagnosticNanCheck() const { }
#endif

		inline Vector3()
			: x(0), y(0), z(0)
		{
			DiagnosticNanCheck();
		}

		inline Vector3(float _x, float _y, float _z)
			: x(x), y(y), z(z)
		{
			DiagnosticNanCheck();
		}

		inline bool ContainsNaN() const
		{
			return (Math::IsNaN(x) || !Math::IsFinite(x) ||
				    Math::IsNaN(y) || !Math::IsFinite(y) ||
				    Math::IsNaN(z) || !Math::IsFinite(z));
		}

		UString ToString() const;

		/*operators*/

		/*

		////////////////////

		          [1]       [2]
			    /    \     /   \
			  [3]   [4]   [1]  [9]
			   |     |
			  [0]   [5]

			  GameObject----
			      

				  MeshComponent    [Component]
				  PhysicsComponent [Component]

		*/

		inline bool operator== (const Vector3& rhs)
		{
			return ( x == rhs.x &&
				     y == rhs.y &&
				     z == rhs.z );
		}

		inline bool operator!= (const Vector3& rhs)
		{
			return !(*this == rhs);
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


		inline VIX_API friend UOStream& operator <<
			(UOStream& o, const Vector3& v)
		{
			o << "Vector3 [ "
				<< v.ToString()
				<< " ]";
			return o;
		}
	};

	inline UString Vector3::ToString() const
	{
		USStream ss;
		ss <<  std::fixed
			<< std::setprecision(3)
			<< "X=" << x << " "
			<< "Y=" << y << " "
			<< "Z=" << z;
		
		return ss.str();
	}
}

#endif