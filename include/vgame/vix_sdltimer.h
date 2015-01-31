#ifndef VIX_SDLTIMER_H
#define VIX_SDLTIMER_H

#include <vix_platform.h>
#include <SDL.h>

namespace Vixen {

	class VIX_API SDLTimer
	{
	public:
		SDLTimer();

		/*start timer*/
		void  Start();

		/*frame tick*/
		void  Tick();

		/*time elapsed between frames*/
		float DeltaTime();

		/*frames per second*/
		float FPS();

		/*calculate fps*/
		void  CalculateFPS();

	private:
		Uint32  m_startTime;
		Uint32  m_curTime;
		Uint32  m_prevTime;
		float   m_fps;
		float   m_deltaTime;
	};

}

#endif
