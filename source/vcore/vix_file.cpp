#include <vix_file.h>

namespace Vixen {

	std::string getFileExtension(const std::string& file, bool wd /* = true */)
	{
		std::string ext = "";
		size_t pos = file.find_first_of(".");
		if (pos != std::string::npos) {
			if (wd)
				ext = file.substr(pos);
			else
				ext = file.substr(pos + 1);
		}

		return ext;
	}

}