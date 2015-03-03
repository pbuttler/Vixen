/*
	The MIT License(MIT)

	Copyright(c) 2014 Matt Guerrette

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files(the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions :
	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
*/

#include <vix_luaengine.h>
#include <vix_debugutil.h>

namespace Vixen {

	LuaEngine::LuaEngine()
	{
		/*create luastate handle*/
		m_L = luaL_newstate();
		/*open standard lua libraries*/
		luaL_openlibs(m_L);
	}

	LuaEngine::~LuaEngine()
	{
		/*close lua state object*/
		lua_close(m_L);
	}

	lua_State* LuaEngine::L()
	{
		return m_L;
	}

	ErrCode LuaEngine::ReportScriptErrors(int state)
	{
		if (state != 0) {
			DebugPrintF(VTEXT("Lua Script Error: %s\n"),
				        lua_tostring(m_L, state));
			lua_pop(m_L, 1); //remove error
			return ErrCode::ERR_FAILURE;
		}

		return ErrCode::ERR_SUCCESS;
	}

	ErrCode LuaEngine::VExecuteFile(const UString& path)
	{
		ErrCode error = ErrCode::ERR_SUCCESS;

		if (path.empty()) {
			DebugPrintF(VTEXT("Failed to execute script file: %s\n"),
				ErrCodeString(ErrCode::ERR_NULL_PATH));
			return ErrCode::ERR_NULL_PATH;
		}

		/*try and execute script file*/
#if defined UNICODE && defined VIX_SYS_WINDOWS
		UConverter cv;
		std::string _path = cv.to_bytes(path);
#else
		std::String _path = path;
#endif
		int state = luaL_dofile(m_L, _path.c_str());
		error = ReportScriptErrors(state);
		if (CheckError(error)) {
			DebugPrintF(VTEXT("Failed to execute script file: %s\n"),
				ErrCodeString(error));
		}
		return error;
	}

	ErrCode LuaEngine::VExecuteExpression(const UString& expression)
	{
		ErrCode error = ErrCode::ERR_SUCCESS;

		if (expression.empty()) {
			DebugPrintF(VTEXT("Failed to execute script expression: %s\n"),
				ErrCodeString(ErrCode::ERR_NULL_PATH));
			return ErrCode::ERR_NULL_PATH;
		}

		/*try and execute script expression*/
#if defined UNICODE && defined VIX_SYS_WINDOWS
		UConverter cv;
		std::string _exp = cv.to_bytes(expression);
#else
		std::String _exp = expression;
#endif
		int state = luaL_dostring(m_L, _exp.c_str());
		error = ReportScriptErrors(state);
		if (CheckError(error)) {
			DebugPrintF(VTEXT("Failed to execute script expression: %s\n"),
				ErrCodeString(error));
		}

		return error;
	}


}