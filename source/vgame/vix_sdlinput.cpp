#include <vix_sdlinput.h>

namespace Vixen {

	SDLKeyboardState::SDLKeyboardState()
	{

	}

	void SDLKeyboardState::KeyDown(SDL_Scancode code)
	{
		m_current[code] = true;
	}

	void SDLKeyboardState::KeyUp(SDL_Scancode code)
	{
		m_current[code] = false;
	}

	void SDLKeyboardState::UpdatePrev()
	{
		m_previous = m_current;
	}

	bool SDLKeyboardState::SingleKeyPress(SDL_Scancode code)
	{
		return m_current[code] && !m_previous[code];
	}

}