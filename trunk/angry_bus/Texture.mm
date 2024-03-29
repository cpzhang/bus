#include "Texture.h"
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#import <QuartzCore/QuartzCore.h>
#include <iostream>
Texture::Texture()
    :_id(0), _referenceCount(0)
{
}

Texture::~Texture()
{
    if(_id)
	glDeleteTextures(1, &_id);
}

bool Texture::create2DFromFile(const std::string& fileName)
{
    glGenTextures(1, &_id);
    glBindTexture(GL_TEXTURE_2D, _id);
    GLsizei width, height;
// border specifies the width of the border. Must be 0.
    static const GLint border = 0;
    GLenum pf;
    unsigned char* data;
    {
        // Creates a Core Graphics image from an image file
        NSString *fn = [NSString stringWithCString:fileName.c_str() 
                                          encoding:[NSString defaultCStringEncoding]];
        CGImageRef spriteImage = [UIImage imageNamed:fn].CGImage;
        // Get the width and height of the image
        width = CGImageGetWidth(spriteImage);
        height = CGImageGetHeight(spriteImage);
        size_t _pixelSize = CGImageGetBitsPerPixel(spriteImage);
        if (_pixelSize == 24)
        {
            pf = GL_RGB;
        }
        else if(_pixelSize == 32)
        {
            pf = GL_RGBA;
        }
        else
        {
            return false;
        }
        size_t bytes = _pixelSize / 8;
        // Allocated memory needed for the bitmap context
        data = (GLubyte *) calloc(width * height * bytes, sizeof(GLubyte));
        // Uses the bitmap creation function provided by the Core Graphics framework. 
        CGContextRef spriteContext;
        if (pf == GL_RGB) 
        {
             spriteContext = CGBitmapContextCreate(data, width, height, 8, width * bytes, CGImageGetColorSpace(spriteImage), kCGImageAlphaNone);
        }
        else
        {
            spriteContext = CGBitmapContextCreate(data, width, height, 8, width * bytes, CGImageGetColorSpace(spriteImage), kCGImageAlphaPremultipliedLast);
            
        }
        if (!spriteContext)
        {
            delete data;
            return false;
        }
        // After you create the context, you can draw the sprite image to the context.
        CGContextDrawImage(spriteContext, CGRectMake(0.0, 0.0, (CGFloat)width, (CGFloat)height), spriteImage);
        // You don't need the context at this point, so you need to release it to avoid memory leaks.
        CGContextRelease(spriteContext);
    }
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    glTexImage2D(GL_TEXTURE_2D, 0, pf, width, height, border, pf, GL_UNSIGNED_BYTE, data);
    GLenum e = glGetError();
    if(e)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, pf, width, height, border, pf, GL_UNSIGNED_BYTE, data);
        std::cout<<"OPenGLES Function Call Error, hint: "<<e<<std::endl;
    }

    _type = eTextureType_2D;
    
    return true;
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

bool Texture::release()
{
    --_referenceCount;
    if (_referenceCount == 0)
    {
        return true;
    }
    
    return false;
}
