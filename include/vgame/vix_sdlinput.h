#ifndef VIX_SDLINPUT_H
#define VIX_SDLINPUT_H

#include <vix_platform.h>
#include <SDL.h>
#include <map>

namespace Vixen {

	class VIX_API SDLKeyboardState
	{
		typedef std::map<SDL_Scancode, bool> KeyState;

	public:
		SDLKeyboardState();

		void KeyDown(SDL_Scancode code);
		void KeyUp(SDL_Scancode code);
		void UpdatePrev();
		bool SingleKeyPress(SDL_Scancode code);
	private:
		KeyState  m_current;
		KeyState  m_previous;
	};

}

#endif