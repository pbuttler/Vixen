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

#ifndef VIX_VECTOR2_H
#define VIX_VECTOR2_H

#include <vix_platform.h>

namespace Vixen {

	class VIX_API Vector2
	{
	public:
		float x;
		float y;
	public:
		inline Vector2()
			: x(0), y(0)
		{

		}

		inline Vector2(float _x, float _y)
			: x(_x), y(_y)
		{

		}


		/*operators*/

		inline bool operator== (const Vector2& rhs)
		{
			return (x == rhs.x &&
				    y == rhs.y);
		}

		inline bool operator!= (const Vector2& rhs)
		{
			return !(*this == rhs);
		}

		//constants
		static const Vector2 Zero;
		static const Vector2 Unit;
		static const Vector2 UnitX;
		static const Vector2 UnitY;
	};

}

#endif