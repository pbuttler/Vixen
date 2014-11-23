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