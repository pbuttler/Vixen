#ifndef VIX_RECTANGLE_H
#define VIX_RECTANGLE_H

#include <vix_platform.h>
#include <iostream>

namespace Vixen {

	class VIX_API Rectangle
	{
	public:
		int x;
		int y;
		int w;
		int h;
	public:
		inline Rectangle()
			: x(0), y(0), w(0), h(0)
		{

		}

		inline Rectangle(int _x, int _y, int _w, int _h)
			: x(_x), y(_y), w(_w), h(_h)
		{

		}

		/*Properties*/
		inline int Left()     const { return x; }
		inline int Right()    const { return x + w; }
		inline int Top()      const { return y; }
		inline int Bottom()   const { return y + h; }

		/*Functions*/

		bool HasValue();

		bool Contains(int x, int y);

		static const Rectangle EMPTY;


		inline VIX_API friend std::ostream& operator << (std::ostream& o, const Rectangle& r)
		{
			o << "Rectangle [ "
				<< "X=" << r.x << " "
				<< "Y=" << r.y << " " 
				<< "W=" << r.w << " " 
				<< "H=" << r.h
				<< " ]";
			return o;
		}
	};

}

#endif