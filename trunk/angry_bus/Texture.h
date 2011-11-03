#ifndef _Texture_
#define _Texture_
#include <string>
class Texture
{
public:
    Texture();
    ~Texture();

    bool create2DFromFile(const std::string& fileName);
    void apply(unsigned int index);
    bool operator=(const Texture& t);
    enum eTextureType
    {
	eTextureType_1D,
	eTextureType_2D,
	eTextureType_3D,
	eTextureType_Cube,
	eTextureType_Size,
    };

    unsigned int _id;
    eTextureType _type;
};
#endif
