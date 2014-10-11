#ifndef VIX_ENUM_UTIL_H
#define VIX_ENUM_UTIL_H

#include <vix_platform.h>
#include <vix_stringutil.h>


template <typename T>
class VIX_API EnumStrings
{
public:
	static char const* m_array[];
};

template <typename T>
const std::string EnumString(T& _enum)
{
	int index = static_cast<int>(_enum);

	const char* str = EnumStrings<T>::m_array[index];
	if (str)
		return std::string(str);
	else
		return "Invalid Enum";
}

#endif