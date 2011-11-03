#ifndef _TextureManager_
#define _TextureManager_
#include "Singleton.h"
class Texture;
class TextureManager : public Singleton<TextureManager>
{
public:
    TextureManager();
    ~TextureManager();

private:
    typedef std::map<std::string, Texture*> NameTextureMap;
    NameTextureMap _textures;
};
#endif
