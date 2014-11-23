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

#ifndef VIX_STRINGUTIL_H
#define VIX_STRINGUTIL_H

#include <vix_platform.h>
#include <string>
#include <sstream>
#include <vector>

#ifndef VIX_BUFSIZE
#define VIX_BUFSIZE 1024
#endif

namespace Vixen {

		VIX_API void str_replaceAll(std::string& input,
			                        const std::string& from, 
			                        const std::string& to);
		template<typename T>
		inline VIX_API std::vector<T> parse(const std::string s, const char delim)
		{
			std::stringstream ss(s);
			std::string item;
			std::vector<T> elems;
			while (std::getline(ss, item, delim)) {
				if (!item.empty()) {
					std::stringstream es(item);
					T t;
					es >> t;
					elems.push_back(t);
				}
			}

			return elems;
		}
}



#endif