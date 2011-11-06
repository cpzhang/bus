#include "Common.h"
float p2m(float p)
{
    return p * scPixel2Meter;
}

float m2p(float m)
{
    return m / scPixel2Meter;
}