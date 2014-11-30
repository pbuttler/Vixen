#ifndef VIX_FMOD_H
#define VIX_FMOD_H

#include <fmod.hpp>
#include <fmod_errors.h>
#include <vix_errglobals.h>
#include <vix_debugutil.h>
#include <vix_stringutil.h>

namespace Vixen {

	inline
	ErrCode FMOD_CheckError(FMOD_RESULT result)
	{
		ErrCode error = ErrCode::ERR_SUCCESS;

		if (result != FMOD_OK)
		{
			error = ErrCode::ERR_FAILURE;

			DebugPrintF(VTEXT("FMOD Error: %s\n%s\n"),
				FMOD_ErrorString(result),
				ErrCodeString(error));
		}

		return error;
	}
}



#endif