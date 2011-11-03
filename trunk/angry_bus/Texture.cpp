#include "Texture.h"
Texture::Texture()
    :_id(0)
{
}

Texture::~Texture()
{
    if(_id)
	glDeleteTexture(1, &_id);
}

bool Texture::create2DFromFile(const std::string& fileName)
{
    glGenTexture(1, &_id);
    glBindTexture(GL_TEXTURE_2D, _id);
    GLsizei width, height;
    GLint border;
    const GLvoid* data;
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, border, GL_RGBA, GL_UNSIGNED_BYTE, data);
// Set the filtering mode
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    _type = eTextureType_2D;
}

void Texture::apply(unsigned int index)
{
    glActiveTexture(index);
    glBindTexture(GL_TEXTURE_2D, _id);
}

bool Texture::operator= (const Texture& t)
{
    if(_id == t._id && _type == t._type)
	return true;
    return false;
}
