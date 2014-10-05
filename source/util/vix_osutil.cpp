#include <vix_osutil.h>

#ifdef VIX_SYS_WINDOWS
	#include <direct.h>   //iso c++
#elif VIX_SYS_LINUX
	#include <sys/stat.h> //linux
#endif

namespace Vixen {

	namespace Util {

		void os_mkdir(const std::string& dir)
		{
#ifdef VIX_SYS_WINDOWS
			_mkdir(dir.c_str());
#elif  VIX_SYS_LINUX
			 mkdir(dir.c_str());
#endif
		}

		bool os_isdir(const std::string& dir)
		{
			//convert path
			std::string path = os_path(dir);
#ifdef VIX_SYS_WINDOWS
			DWORD dwAttrib = GetFileAttributesA(path.c_str());
			return (dwAttrib != INVALID_FILE_ATTRIBUTES &&
				   (dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
#elif VIX_SYS_LINUX
			return false;
#endif
		}

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