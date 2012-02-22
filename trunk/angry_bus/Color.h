#ifndef _Color_
#define _Color_
class Color
{
public:
    Color();
    Color(float r, float g, float b, float a);
    float red, green, blue, alpha;
    static const Color White;
};
#endif
