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

#include <vix_osutil.h>

#ifdef VIX_SYS_WINDOWS
	#include <direct.h>   //iso c++
#elif VIX_SYS_LINUX
	#include <sys/stat.h> //linux
#endif

namespace Vixen {


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
		DWORD dwAttrib = GetFileAttributesA(dir.c_str());
		return (dwAttrib != INVALID_FILE_ATTRIBUTES &&
				(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
#elif VIX_SYS_LINUX
		//THIS CODE *SHOULD* WORK ON LINUX AND UNIX.
		//IM NOT 100% POSITIVE THOUGH, SO PLEASE CHECK
		struct stat info;
		stat(dir.c_str(), &info);
		return S_ISDIR(info.st_mode);
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
		c_slash = WIN_PATH_DELIM;
		back_slash = dir.find_last_of(c_slash);
#else
		c_slash = UNIX_PATH_DELIM;
		back_slash = dir.find_last_of(c_slash);
#endif
		if (back_slash != std::string::npos)
			dir = dir.substr(0, back_slash);
		if (wt)
			dir += c_slash;

		return dir;

	}

}