#ifndef _Vector2_
#define _Vector2_
#include "Common.h"
class Vector2
{
public:
    float x, y;
    inline Vector2( const Real fX, const Real fY)
	: x( fX ), y( fY )
    {
    }
};
#endif
