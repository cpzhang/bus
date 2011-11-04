#include "Shader.h"
#import <QuartzCore/QuartzCore.h>
#include <iostream>
Shader::Shader()
:_shader(0)
{
    
}

Shader::~Shader()
{
    glDeleteShader(_shader);
}

void Shader::setFile(std::string const &fileName)
{
    _fileName = fileName;
}

void Shader::setName(std::string const &name)
{
    _name = name;
}

std::string Shader::getName()
{
    return _name;
}

void Shader::setType(GLenum shaderType)
{
    _type = shaderType;
}

bool Shader::build()
{
    NSString* fn = [NSString stringWithCString:_fileName.c_str() encoding:[NSString defaultCStringEncoding]];
    NSString* path = [[NSBundle mainBundle] pathForResource:fn ofType:nil];//
    const GLchar* source = (GLchar*)[[NSString stringWithContentsOfFile:path encoding:NSUTF8StringEncoding error:nil] UTF8String];
    if (!source)
    {
        NSLog(@"Failed to load shader file");
        return false;
    }
    _shader = glCreateShader(_type);
    if(!_shader) return false;
    glShaderSource(_shader, 1, &source, NULL);
    glCompileShader(_shader);
    //
    GLint status;
    glGetShaderiv(_shader, GL_COMPILE_STATUS, &status);
    if (!status)
    {
        GLint infoLen = 0;
        glGetShaderiv(_shader, GL_INFO_LOG_LENGTH, &infoLen);
        if(infoLen > 0)
        {
            static char sError[512];
            glGetShaderInfoLog(_shader, infoLen, NULL, sError);
            std::cout<<"build shader failed! hint: "<<sError<<std::endl;
        }
        return false;
    }
    
    return true;
}

GLuint Shader::getID()
{
    return _shader;
}
