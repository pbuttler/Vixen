#ifndef VIX_SINGLETON_H
#define VIX_SINGLETON_H

#include <vix_platform.h>
#include <vix_interfaces.h>
#include <cassert>
#include <memory>

namespace Vixen {

	namespace System {

		template <typename T>
		class VIX_API Singleton : protected INonCopyable
		{
		public:
			static T& instance()
			{
				static T _instance;

				return _instance;
			}

		protected:
			explicit Singleton<T>() 
			{
		
			}
		
		};
	}
}

#endif