#ifndef VIX_SCRIPTENGINE_H
#define VIX_SCRIPTENGINE_H

#include <vix_platform.h>
#include <vix_errglobals.h>
#include <vix_stringutil.h>
#include <vix_noncopy.h>

namespace Vixen {

	class VIX_API IScriptEngine : INonCopy
	{
	public:
		virtual ~IScriptEngine() { }
		
		virtual ErrCode VExecuteFile(const UString& path) = 0;
		virtual ErrCode VExecuteExpression(const UString& expression) = 0;
	};

}

#endif