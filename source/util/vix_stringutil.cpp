#include <vix_stringutil.h>

namespace Vixen {

	void str_replaceAll(std::string& input, const std::string& from, const std::string& to)
	{
		size_t pos = 0;
		while ((pos = input.find(from, pos)) != std::string::npos) {
			input.replace(pos, from.length(), to);
			pos += to.length();
		}
	}
}
