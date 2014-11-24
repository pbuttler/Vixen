#include <vix_rectangle.h>

namespace Vixen {

	const Rectangle Rectangle::EMPTY(0, 0, 0, 0);

	/*Checks whether given point is bounded by Rectangle*/
	bool Rectangle::Contains(int x, int y)
	{
		return ((((this->x <= x) && (x < (this->x + this->w)))
			   && (this->y <= y)) && (y < (this->y + this->h)));
	}

	/*Checks whether Rectangle has any value*/
	bool Rectangle::HasValue()
	{
		return x != 0 || y != 0 || w != 0 || h != 0;
	}

}