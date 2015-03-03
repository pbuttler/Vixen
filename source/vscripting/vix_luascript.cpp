#include <vix_luascript.h>
#include <vix_debugutil.h>
#include <vix_luaengine.h>

namespace Vixen {

	const UString LuaScript::OBJECT_TABLE = VTEXT("_GO");
	const UString LuaScript::AWAKE_FUNC = VTEXT("OnAwake");
	const UString LuaScript::UPDATE_FUNC = VTEXT("OnUpdate");
	const UString LuaScript::LATEUPDATE_FUNC = VTEXT("OnLateUpdate");
	const UString LuaScript::AWAKE_FULL_SIGN = LuaScript::OBJECT_TABLE +
		VTEXT(".") +
		LuaScript::AWAKE_FUNC;
	const UString LuaScript::UPDATE_FULL_SIGN = LuaScript::OBJECT_TABLE +
		VTEXT(".") +
		LuaScript::UPDATE_FUNC;
	const UString LuaScript::LATEUPDATE_FULL_SIGN = LuaScript::OBJECT_TABLE +
		VTEXT(".") +
		LuaScript::LATEUPDATE_FUNC;


	LuaScript::LuaScript(LuaScriptInfo info)
	{
		m_info = info;
		m_awakeFunc = NULL;
		m_updateFunc = NULL;
		m_lateUpdateFunc = NULL;
	}

	LuaScript::~LuaScript()
	{
		delete m_awakeFunc;
		delete m_updateFunc;
		delete m_lateUpdateFunc;
	}

	ErrCode LuaScript::Load(LuaEngine* engine, LuaScriptInfo info)
	{
		if (!engine) {
			DebugPrintF(VTEXT("Error loading LuaScript [No engine]: %s\n"),
				ErrCodeString(ErrCode::ERR_FAILURE));
			return ErrCode::ERR_FAILURE;
		}

		if (info.file.empty() && info.raw.empty()) {
			DebugPrintF(VTEXT("Error loading LuaScript [No contents]: %s\n"),
				ErrCodeString(ErrCode::ERR_FAILURE));
			return ErrCode::ERR_FAILURE;
		}

		/*load script file*/
		if (!info.file.empty())
		{
			engine->VExecuteFile(info.file);
		}
		/*load raw script expression*/
		else
		{
			engine->VExecuteExpression(info.raw);
		}

		/*store lua function reference*/
		return InitFuncRefs(engine);
	}

	ErrCode LuaScript::InitFuncRefs(LuaEngine* engine)
	{
#ifdef UNICODE && VIX_SYS_WINDOWS
		UConverter cv;
		std::string _awake = cv.to_bytes(AWAKE_FULL_SIGN);
		std::string _update = cv.to_bytes(UPDATE_FULL_SIGN);
		std::string _lateUpdate = cv.to_bytes(LATEUPDATE_FULL_SIGN);
#else
		std::string _awake = AWAKE_FULL_SIGN;
		std::string _update = UPDATE_FULL_SIGN;
		std::string _lateUpdate = LATEUPDATE_FULL_SIGN;
#endif
		m_awakeFunc = new LuaRef(engine->L(), _awake.c_str());
		m_updateFunc = new LuaRef(engine->L(), _update.c_str());
		m_lateUpdateFunc = new LuaRef(engine->L(), _lateUpdate.c_str());
		if (!m_awakeFunc ||
			!m_updateFunc ||
			!m_lateUpdateFunc)
		{
			DebugPrintF(VTEXT("Error Initiliazing Ref Funcs: %s\n"),
				ErrCodeString(ErrCode::ERR_FAILURE));
			return ErrCode::ERR_FAILURE;
		}

		return ErrCode::ERR_SUCCESS;
	}

	ErrCode LuaScript::Awake()
	{
		if (!m_awakeFunc) {
			DebugPrintF(VTEXT("Error calling Awake(). Null function\n%s\n"),
				ErrCodeString(ErrCode::ERR_FAILURE));
			return ErrCode::ERR_FAILURE;
		}

		m_awakeFunc->call();
	}

	ErrCode LuaScript::Update()
	{
		if (!m_updateFunc) {
			DebugPrintF(VTEXT("Error calling Update(). Null function\n%s\n"),
				ErrCodeString(ErrCode::ERR_FAILURE));
			return ErrCode::ERR_FAILURE;
		}

		m_updateFunc->call();
	}

	ErrCode LuaScript::LateUpdate()
	{
		if (!m_lateUpdateFunc) {
			DebugPrintF(VTEXT("Error calling LateUpdate(). Null function\n%s\n"),
				ErrCodeString(ErrCode::ERR_FAILURE));
			return ErrCode::ERR_FAILURE;
		}

		m_lateUpdateFunc->call();
	}

}