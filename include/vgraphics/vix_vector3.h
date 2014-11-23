#ifndef VIX_VECTOR3_H
#define VIX_VECTOR3_H

#include <vix_platform.h>
#include <vix_math.h>
#include <sstream>

namespace Vixen {

	class VIX_API Vector3
	{
	public:
		float m_x;
		float m_y;
		float m_z;
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
			: m_x(0), m_y(0), m_z(0)
		{
			DiagnosticNanCheck();
		}

		inline Vector3(float x, float y, float z)
			: m_x(x), m_y(y), m_z(z)
		{
			DiagnosticNanCheck();
		}

		inline bool ContainsNaN() const
		{
			return (Math::IsNaN(m_x) || !Math::IsFinite(m_x) ||
				    Math::IsNaN(m_y) || !Math::IsFinite(m_y) ||
				    Math::IsNaN(m_z) || !Math::IsFinite(m_z));
		}

		std::string ToString() const;

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


		inline VIX_API friend std::ostream& operator <<
			(std::ostream& o, const Vector3& v)
		{
			o << "Vector3 [ "
				<< v.ToString()
				<< " ]";
			return o;
		}
	};

	inline std::string Vector3::ToString() const
	{
		std::stringstream ss;
		ss << std::fixed
			<< std::setprecision(3)
			<< "X=" << m_x << " "
			<< "Y=" << m_y << " "
			<< "Z=" << m_z;
		
		return ss.str();
	}
}

#endif