#ifndef VIX_SDLINPUT_H
#define VIX_SDLINPUT_H

#include <vix_platform.h>
#include <SDL.h>
#include <map>

namespace Vixen {

	class VIX_API SDLKeyboardState
	{
	public:
		SDLKeyboardState();


	private:
		Uint8* m_curKeyState;
		Uint8* m_prevKeyState;
	};

}

#endif