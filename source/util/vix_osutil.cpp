#include <vix_osutil.h>

namespace Vixen {

	namespace Util {

		std::string os_path(const std::string& path)
		{
			std::string temp = path;
#ifdef VIX_SYS_WINDOWS
			str_replaceAll(temp, "/", "\\");
#else
			str_replaceAll(temp, "\\", "/");
#endif
			return temp;
		}

		std::string os_dir(const std::string& path, bool wt)
		{
			std::string dir = "";
			if (path.empty())
				return dir;

			//remove trailing slash for now
			dir = path.substr(0, path.size() - 1);

			size_t back_slash = 0;
			char   c_slash;
#ifdef VIX_SYS_WINDOWS
			c_slash = '\\';
			back_slash = dir.find_last_of(c_slash);
#else
			c_slash = '/';
			back_slash = dir.find_last_of(c_slash);
#endif
			if (back_slash != std::string::npos)
				dir = dir.substr(0, back_slash);
			if (wt)
				dir += c_slash;

			return dir;

		}
	}

}