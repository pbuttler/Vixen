#ifndef VIX_MATH_H
#define VIX_MATH_H

#include <vix_platform.h>
#include <vix_debugutil.h>

#include <cmath>

namespace Vixen {

	const float PI = 3.141593f;
	const float HALF_PI = 1.5707965f;
	const float TWO_PI = 6.283186f;

	class VIX_API Math
	{
	public:

		static bool IsNaN(float n);
		static bool IsFinite(float n);
	};
}


#endif