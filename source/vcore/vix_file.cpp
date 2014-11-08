#include <vix_file.h>

namespace Vixen {

	std::string getFileExtension(const std::string& filePath, bool wd /* = true */)
	{
		std::string ext = "";
		size_t pos = filePath.find_first_of(".");
		if (pos != std::string::npos) {
			if (wd)
				ext = filePath.substr(pos);
			else
				ext = filePath.substr(pos + 1);
		}

		return ext;
	}

	std::string getFileName(const std::string& filePath)
	{
		std::string name = "";
		std::string path = os_path(filePath);
		size_t pos = 0;
#ifdef VIX_SYS_WINDOWS
		pos = path.find_last_of(WIN_PATH_DELIM);
		if(pos != std::string::npos) {
			path.erase(0, pos + 1);
		}
#elif defined (VIX_SYS_LINUX) || defined (VIX_SYS_MACOS)
		pos = path.find_last_of(UNIX_PATH_DELIM);
		if (pos != std::string::npos) {
			path.erase(0, pos + 1);
		}
#endif

		return path;
	}

}