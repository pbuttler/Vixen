#include <vix_errglobals.h>
#include <vix_enumutil.h>

template <>
char const* EnumStrings<ErrCode>::m_array[] =
{
	"ERR_FAILURE",
	"ERR_SUCCESS",
	"ERR_FILE_NOT_FOUND",
	"ERR_FILE_FOUND",
	"ERR_SDL_INIT",
	"ERR_SDL_CREATE_WINDOW"
};