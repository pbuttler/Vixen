#ifndef VIX_NONCOPY_H
#define VIX_NONCOPY_H

#include <vix_platform.h>

namespace Vixen {

	class VIX_API INonCopy
	{
	protected:
		INonCopy() { }
		~INonCopy() { }

	private:
		INonCopy(const INonCopy&);
		const INonCopy& operator= (const INonCopy&);
	};

}

#endif