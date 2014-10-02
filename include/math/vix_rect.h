#ifndef VIX_RECT_H
#define VIX_RECT_H

#include <vix_platform.h>

namespace Vixen {

	namespace Math {

		class VIX_API Rect
		{
		public:
			int x;
			int y;
			int width;
			int height;

		public:
			Rect()
			{
				x = 0;
				y = 0;
				width = 0;
				height = 0;
			}

			Rect(int _x, int _y, int _width, int _height)
			{
				x = _x;
				y = _y;
				width = _width;
				height = _height;
			}
			
			int left()	{ return x; }
			int right() { return x + width; }
			int top()	{ return y; }
			int bottom(){ return y + height; }
			bool hasValue()
			{
				return x != 0 || y != 0 || width != 0 || height != 0;
			}

			bool contains(int x, int y);

			static const Rect EMPTY;
		};

	}
}

#endif