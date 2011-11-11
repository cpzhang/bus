#ifndef _Vector3_
#define _Vector3_
#include "Common.h"
class Vector3
{
public:
    float x, y, z;
    
    inline Vector3()
    :x(0.0), y(0.0), z(0.0)
    {
        
    }
    inline Vector3( const Real fX, const Real fY, const Real fZ )
	: x( fX ), y( fY ), z( fZ )
    {
    }
    
    inline Vector3(const Vector3& fv)
	:x(fv.x), y(fv.y), z(fv.z)
    {
    }
    
    inline Vector3 operator * (float s)
    {
        return Vector3(x * s, y * s, z * s);
    }
    
    inline Vector3 operator / (float s)
    {
        return Vector3(x / s, y / s, z / s);
    }
    
    static const Vector3 ZERO;
};
#endif
