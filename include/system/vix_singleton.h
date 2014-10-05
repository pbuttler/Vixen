#ifndef VIX_SINGLETON_H
#define VIX_SINGLETON_H

#include <vix_platform.h>
#include <vix_interfaces.h>
#include <cassert>

namespace Vixen {

	namespace System {

		template <typename T>
		class VIX_API Singleton : public INonCopyable
		{
		protected:
			static T* _data;

		public:
			Singleton(void)
			{
				assert(!_data);
				_data = static_cast<T*>(this);
			}

			~Singleton(void)
			{
				assert(_data);
				_data = nullptr;
			}

			static T& instance()
			{
				return *_data;
			}

			static T* instancePtr()
			{
				return _data;
			}
		};

	}
}

#endif