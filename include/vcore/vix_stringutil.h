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