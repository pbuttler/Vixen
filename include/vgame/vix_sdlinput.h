#ifndef VIX_SDLINPUT_H
#define VIX_SDLINPUT_H

#include <vix_platform.h>
#include <vix_input.h>
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
		bool KeyPress(IKEY key);
		bool SingleKeyPress(IKEY key);
	private:
		KeyState  m_current;
		KeyState  m_previous;

		SDL_Scancode convertFromIKEY(IKEY key);
	};

}

#endif