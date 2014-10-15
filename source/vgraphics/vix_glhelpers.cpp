#include <vix_glhelpers.h>
#include <vector>
#include <sstream>

namespace Vixen {

	std::vector<std::string> GLSupportedExt()
	{
		std::vector<std::string> v;

		char* extensions = (char*)glGetString(GL_EXTENSIONS);
		std::string s(extensions);
		std::stringstream ss(s);
		std::copy(std::istream_iterator<std::string>(ss),
			std::istream_iterator<std::string>(), std::back_inserter(v));

		return v;
	}
}

