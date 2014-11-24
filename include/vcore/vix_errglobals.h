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

#ifndef VIX_ERR_GLOBALS_H
#define VIX_ERR_GLOBALS_H

#include <vix_platform.h>
#include <vix_stringutil.h>

enum class ErrCode
{
	ERR_FAILURE,
	ERR_SUCCESS,
	ERR_NULL_PATH,
	ERR_FILE_NOT_FOUND,
	ERR_SDL_INIT_FAIL,
	ERR_SDL_CREATE_FAIL,
	ERR_IMAGE_LOAD_FAIL
};

inline std::string ErrCodeString(ErrCode error)
{
	std::string errorMsg;

	switch (error)
	{
	case ErrCode::ERR_FAILURE:
		errorMsg = "ERR_FAILURE";
		break;
	case ErrCode::ERR_SUCCESS:
		errorMsg = "ERR_SUCCESS";
		break;
	case ErrCode::ERR_NULL_PATH:
		errorMsg = "ERR_NULL_PATH";
		break;
	case ErrCode::ERR_FILE_NOT_FOUND:
		errorMsg = "ERR_FILE_NOT_FOUND";
		break;
	case ErrCode::ERR_SDL_CREATE_FAIL:
		errorMsg = "ERR_SDL_CREATE_FAIL";
		break;
	case ErrCode::ERR_SDL_INIT_FAIL:
		errorMsg = "ERR_SDL_INIT_FAIL";
		break;
	case ErrCode::ERR_IMAGE_LOAD_FAIL:
		errorMsg = "ERR_IMAGE_LOAD_FAIL";
		break;

	default:
		errorMsg = "UNKNOWN ERROR";
		break;
	}

	return errorMsg;
}

inline bool CheckError(ErrCode error)
{
	return error != ErrCode::ERR_SUCCESS;
}


#endif