#ifndef VIX_GAMECONFIG_H
#define VIX_GAMECONFIG_H

#include <vix_platform.h>
#include <vix_noncopy.h>
#include <vix_stringutil.h>
#include <vix_errglobals.h>
#include <vix_tinyxml.h>
#include <vix_sdlwindow.h>

namespace Vixen {

	class VIX_API GameConfig : public INonCopy
	{
	public:
		GameConfig(const UString& path);

		/*Accessors for loaded data*/

		SDL_GW_Params WindowArgs() const;

	private:
		ErrCode LoadConfig(const UString& path);

	private:
		SDL_GW_Params m_windowArgs;
		UString       m_path;
	};
}

#endif