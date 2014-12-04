#ifndef VIX_LUASCRIPT_H
#define VIX_LUASCRIPT_H

#include <vix_platform.h>
#include <vix_lua.h>
#include <vix_stringutil.h>
#include <map>

namespace Vixen {

	/* LuaScript class
	*
	*  Desc:
	*  This class describes a LuaScript object that can be attached to any
	*  gameobject in order for user to implement scripting logic in predefined
	*  functions.
	*
	*  Functions:
	*
	*  OnAwake()      - called to initialize script object before scene starts
	*
	*  OnUpdate()     - called every frame during game update
	*
	*  OnLateUpdate() - called after all calls to Update have been processed
	*/
	class VIX_API LuaScript
	{
		typedef LuaIntf::LuaRef LuaRef;

	public:
		LuaScript(const UString& path);

		~LuaScript();

		/*load script file*/
		ErrCode LoadFromFile()
	private:
		LuaRef* m_awakeFunc;
		LuaRef* m_updateFunc;
		LuaRef* m_lateUpdateFunc;
	};

}

#endif

