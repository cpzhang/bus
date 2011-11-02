#ifndef _Vector3_
#define _Vector3_
#include "Common.h"
class Vector3
{
public:
    float x, y, z;
    inline Vector3( const Real fX, const Real fY, const Real fZ )
	: x( fX ), y( fY ), z( fZ )
    {
    }
};
#endif
