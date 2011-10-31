//
//  Shader.cpp
//  angry_bus
//
//  Created by suning on 11-10-31.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#include "Shader.h"
#import <QuartzCore/QuartzCore.h>
#include <iostream>
Shader::Shader()
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
    glShaderSource(_shader, 1, &source, NULL);
    glCompileShader(_shader);
    //
    GLint status;
    glGetShaderiv(_shader, GL_COMPILE_STATUS, &status);
    if (status == 0)
    {
        glDeleteShader(_shader);
        return false;
    }
    
    return true;
}

GLuint Shader::getID()
{
    return _shader;
}