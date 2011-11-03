#ifndef _TextureManager_
#define _TextureManager_
#include "Singleton.h"
#include <map>
#include <string>
class Texture;
class TextureManager : public Singleton<TextureManager>
{
public:
    TextureManager();
    ~TextureManager();

    Texture* createTextureFromImageFile(const std::string& f);
    void discardTexture(Texture* t);
    
private:
    typedef std::map<std::string, Texture*> NameTextureMap;
    NameTextureMap _textures;
};
#endif
