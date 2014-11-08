#ifndef VIX_ERR_GLOBALS_H
#define VIX_ERR_GLOBALS_H

#include <vix_platform.h>
#include <vix_stringutil.h>

enum class ErrCode
{
	ERR_FAILURE,
	ERR_SUCCESS,
	ERR_FILE_NOT_FOUND,
	ERR_FILE_FOUND,
	ERR_SDL_INIT,
	ERR_SDL_CREATE_WINDOW,
	ERR_IMAGE_LOAD_FAILURE
};

inline bool CheckError(ErrCode err)
{
	if (err != ErrCode::ERR_SUCCESS)
		return false;
	else
		return true;
}




#endif