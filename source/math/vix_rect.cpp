#include <vix_rect.h>

namespace Vixen {

	namespace Math {

		const Rect Rect::EMPTY(0, 0, 0, 0);

		bool Rect::contains(int x, int y)
		{
			return ((((this->x <= x) && (x < (this->x + this->width)))
				&& (this->y <= y)) && (y < (this->y + this->height)));
		}
	}
}