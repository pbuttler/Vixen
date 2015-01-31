#include <vix_sdltimer.h>

namespace Vixen {

	SDLTimer::SDLTimer()
	{
		m_startTime = 0;
		m_curTime = 0;
		m_prevTime = 0;
		m_fps = 0.0f;
	}

	void SDLTimer::Start()
	{
		m_startTime = SDL_GetTicks();
	}

	void SDLTimer::Tick()
	{
		/*cache current time in prev*/
		m_prevTime = m_curTime;

		m_curTime = SDL_GetTicks();

		/*calculate delta time*/
		m_deltaTime = (float)(m_curTime - m_prevTime) / 1000.0f;
	}

	void SDLTimer::CalculateFPS()
	{
		static int frameCnt = 0;
		
		if (m_startTime < (SDL_GetTicks() - 1000.0f))
		{
			m_startTime = SDL_GetTicks();
			m_fps = (float)frameCnt;

			frameCnt = 0;
		}

		++frameCnt;
	}

	float SDLTimer::DeltaTime()
	{
		return m_deltaTime;
	}

	float SDLTimer::FPS()
	{
		return m_fps;
	}
}