#ifndef VIX_LUASCRIPT_H
#define VIX_LUASCRIPT_H

#include <vix_platform.h>
#include <vix_lua.h>
#include <vix_stringutil.h>
#include <vix_errglobals.h>
#include <vix_tinyxml.h>

namespace Vixen {

	struct LuaScriptInfo
	{
		UString file;
		UString raw;
	};

	class LuaEngine;

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

		/*CONTANTS*/
	public:
		static const UString OBJECT_TABLE;
		static const UString AWAKE_FUNC;
		static const UString UPDATE_FUNC;
		static const UString LATEUPDATE_FUNC;
		static const UString AWAKE_FULL_SIGN;
		static const UString UPDATE_FULL_SIGN;
		static const UString LATEUPDATE_FULL_SIGN;

	public:
		LuaScript(LuaScriptInfo info);

		~LuaScript();

		/*load script file*/
		ErrCode Load(LuaEngine* engine, LuaScriptInfo info);

		/*get script info*/
		LuaScriptInfo Info();

		/*awake*/
		ErrCode Awake();

		/*update*/
		ErrCode Update();

		/*late update*/
		ErrCode LateUpdate();

	private:
		LuaScriptInfo      m_info;
		LuaRef*            m_awakeFunc;
		LuaRef*            m_updateFunc;
		LuaRef*            m_lateUpdateFunc;

		ErrCode InitFuncRefs(LuaEngine* engine);
	};

}

#endif

