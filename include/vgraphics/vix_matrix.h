#ifndef VIX_MATRIX_H
#define VIX_MATRIX_H

#include <vix_platform.h>
#include <vix_math.h>
#include <vix_vector3.h>
#include <iostream>

namespace Vixen {

	/*
	*	4x4 Matrix class
	*/
	class VIX_API Matrix
	{
	public:
		float m[4][4];

	public:
		Matrix()
		{
			initMatrix(0, 0, 0, 0,
				       0, 0, 0, 0,
				       0, 0, 0, 0,
				       0, 0, 0, 0);
		}

		Matrix(float m11, float m12, float m13, float m14,
			   float m21, float m22, float m23, float m24,
			   float m31, float m32, float m33, float m34,
			   float m41, float m42, float m43, float m44)
		{
			initMatrix(m11, m12, m12, m14,
					   m21, m22, m23, m24,
				       m31, m32, m33, m34,
				       m41, m42, m43, m44);
		}

		Matrix Left()		const;
		Matrix Right()		const;
		Matrix Forward()	const;
		Matrix Backward()	const;
		Matrix Up()			const;
		Matrix Down()		const;


		//operator overloads
		float*			operator[] (size_t row);
		const float*	operator[] (size_t row) const;


		//static members
		static const Matrix Identity;



		inline VIX_API friend std::ostream& operator <<
			(std::ostream& o, const Matrix& m)
		{
			o << "Matrix\n"
				<< "[ " << m[0][0] << ", " << m[0][1] << ", " << m[0][2] << ", " << m[0][3] << "]\n"
				<< "[ " << m[1][0] << ", " << m[1][1] << ", " << m[1][2] << ", " << m[1][3] << "]\n"
				<< "[ " << m[2][0] << ", " << m[2][1] << ", " << m[2][2] << ", " << m[2][3] << "]\n"
				<< "[ " << m[3][0] << ", " << m[3][1] << ", " << m[3][2] << ", " << m[3][3] << "]\n";
			return o;
		}

	private:
		void initMatrix(float m11, float m12, float m13, float m14,
						float m21, float m22, float m23, float m24,
						float m31, float m32, float m33, float m34,
						float m41, float m42, float m43, float m44);
	};
}

#endif