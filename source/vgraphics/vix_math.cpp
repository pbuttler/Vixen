#include <vix_math.h>

namespace Vixen {

	bool Math::IsNaN(float n)
	{
		return std::isnan(n);
	}

	bool Math::IsFinite(float n)
	{
		return std::isfinite(n);
	}

}