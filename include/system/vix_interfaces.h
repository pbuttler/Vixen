#ifndef VIX_INTERFACES_H
#define VIX_INTERFACES_H

#include <vix_platform.h>

namespace Vixen {

	namespace System {

		class VIX_API INonCopyable
		{
		protected:
			INonCopyable() { }

		private:
			INonCopyable(const INonCopyable&);
			INonCopyable& operator= (const INonCopyable&);
		};

		class VIX_API IApplication : INonCopyable
		{
		public:
			virtual ~IApplication() { }

			virtual bool initialized() = 0; //application init state
			virtual int  run() = 0;			//application loop
		};

		class VIX_API IContent;

	}
}

#endif