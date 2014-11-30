#include <vix_luascriptmanager.h>

namespace Vixen {

	
	LuaScriptManager::LuaScriptManager()
	{

	}

	LuaScriptManager::~LuaScriptManager()
	{

	}

	LuaEngine* const LuaScriptManager::Engine()
	{
		return m_engine;
	}

	ErrCode LuaScriptManager::VStartUp()
	{
		ErrCode error = ErrCode::ERR_SUCCESS;

		/*create lua engine*/
		m_engine = new LuaEngine;


		return error;
	}

	ErrCode LuaScriptManager::VShutDown()
	{
		ErrCode error = ErrCode::ERR_SUCCESS;

		/*destroy lua engine*/
		delete m_engine;

		return error;
	}

}