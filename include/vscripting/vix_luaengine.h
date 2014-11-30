#ifndef VIX_LUAENGINE_H
#define VIX_LUAENGINE_H

#include <vix_platform.h>
#include <vix_scriptengine.h>
#include <vix_lua.h>

namespace Vixen {

	class VIX_API LuaEngine : public IScriptEngine
	{
		/*lua state object*/
		lua_State* m_L;
	public:
		LuaEngine();

		~LuaEngine();

		lua_State* L();

		/*Execute Lua script file*/
		ErrCode VExecuteFile(const UString& path) override;
		
		/*Execute Lua expression*/
		ErrCode VExecuteExpression(const UString& expression) override;

	private:
		/*report errors in evaluated lua scripts*/
		ErrCode ReportScriptErrors(int state);
	};

}

#endif
