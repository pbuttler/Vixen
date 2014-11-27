#include <vix_gameconfig.h>

namespace Vixen {

	GameConfig::GameConfig(const UString& path)
	{
		LoadConfig(path);
	}

	ErrCode GameConfig::LoadConfig(const UString& path)
	{
		return ErrCode::ERR_SUCCESS;
	}

	SDL_GW_Params GameConfig::WindowArgs() const
	{
		return m_windowArgs;
	}

}