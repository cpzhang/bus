#include "TextureManager.h"
#include "Texture.h"
TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
    for (NameTextureMap::iterator it = _textures.begin(); it != _textures.end(); ++it)
    {
        Texture* t = it->second;
        delete t;
        t = NULL;
    }
    _textures.clear();
}

Texture* TextureManager::createTextureFromImageFile(const std::string& f)
{
    Texture* t = NULL;
    NameTextureMap::iterator it = _textures.find(f);
    if (it == _textures.end())
    {
        t = new Texture;
        if(!t->create2DFromFile(f))
        {
            delete t;
            t = NULL;
        }
        else
        {
            _textures[f] = t;
            t->_referenceCount++;
        }
    }
    else
    {
        t = it->second;
        t->_referenceCount++;
    }
    
    return t;
}
void TextureManager::discardTexture(Texture* t)
{
    for (NameTextureMap::iterator it = _textures.begin(); it != _textures.end(); ++it)
    {
        if(it->second == t)
        {
            if(t->release())
            {
                delete t;
                t = NULL;
                _textures.erase(it);
                break;
            }
        }
    }
}
