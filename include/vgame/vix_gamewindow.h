#ifndef VIX_GAMEWINDOW_H
#define VIX_GAMEWINDOW_H

#include <vix_platform.h>
#include <vix_noncopy.h>
#include <vix_stringutil.h>
#include <vix_errglobals.h>
#include <vix_rectangle.h>

namespace Vixen {

	class VIX_API IGameWindow : INonCopy
	{

	public:
		virtual ~IGameWindow() { }

		virtual ErrCode            VInit() = 0;
		virtual void               VSetFullscreen(bool flag) = 0;
		virtual void               VSetVisible(bool flag) = 0;
		virtual void               VSwapBuffers() = 0;
		virtual const UString&     VGetTitle() = 0;
		virtual const Rect&        VGetClientBounds() = 0;

		static const size_t DEF_WINDOW_WIDTH = 800;
		static const size_t DEF_WINDOW_HEIGHT = 600;
	};

}


#endif