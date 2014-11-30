#ifndef VIX_LUASCRIPTMANAGER_H
#define VIX_LUASCRIPTMANAGER_H

#include <vix_platform.h>
#include <vix_singleton.h>
#include <vix_luaengine.h>
#include <vix_manager.h>

namespace Vixen {

	class VIX_API LuaScriptManager : public Singleton < LuaScriptManager >, IManager
	{
		friend class Singleton < LuaScriptManager >;
	public:
		/*constructor (NOTE: intialization occurs in VStartUp()*/
		LuaScriptManager();

		/*desturctor (NOTE: destruction occurs in VShutDown()*/
		~LuaScriptManager();

		/*Initialize LuaScriptManager*/
		ErrCode VStartUp()  override;

		/*Destruct LuaScriptManager*/
		ErrCode VShutDown() override;

		LuaEngine* const Engine();
	private:
		LuaEngine*  m_engine;
	};

	LuaScriptManager& g_LuaScriptManager = LuaScriptManager::instance();
}

#endif
