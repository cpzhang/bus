//
//  Program.cpp
//  angry_bus
//
//  Created by suning on 11-10-29.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//
#include "Program.h"
#import <QuartzCore/QuartzCore.h>

Program::Program()
:_program(0), _vs(0), _fs(0)
{
    
}
Program::~Program()
{
    
}
void Program::setVertexShaderFile(const std::string& vs)
{
    _vsFile = vs;
}
void Program::setFragmentShaderFile(const std::string& fs)
{
    _fsFile = fs;
}
GLuint Program::getProgram()
{
    if (_program == 0)
    {
        buildProgram();
    }
    return _program;
}
bool Program::buildProgram()
{
    _vs = buildShader(GL_VERTEX_SHADER, _vsFile);
    if (_vs == 0)
    {
        NSLog(@"Failed to build Vertex Shader");
        return false;
    }
    _fs = buildShader(GL_FRAGMENT_SHADER, _fsFile);
    if (_fs == 0)
    {
        NSLog(@"Failed to build Fragment Shader");
        return false;
    }
    _program = glCreateProgram();
    glAttachShader(_program, _vs);
    glAttachShader(_program, _fs);
    glLinkProgram(_program);
    GLint status;
    glGetProgramiv(_program, GL_LINK_STATUS, &status);
    if (status ==  GL_FALSE)
    {
        NSLog(@"Failed to build Program");
        return false;
    }

    return true;
}
GLuint Program::buildShader(GLenum st, std::string const &s)
{
    NSString* path = [NSString stringWithCString:s.c_str() encoding:[NSString defaultCStringEncoding]];
    const GLchar* source = (GLchar*)[[NSString stringWithContentsOfFile:path encoding:NSUTF8StringEncoding error:nil] UTF8String];
    if (!source)
    {
        NSLog(@"Failed to load shader file");
        return 0;
    }
    GLuint handle = glCreateShader(st);
    glShaderSource(handle, 1, &source, NULL);
    glCompileShader(handle);
    //
    GLint status;
    glGetShaderiv(handle, GL_COMPILE_STATUS, &status);
    if (status == 0)
    {
        glDeleteShader(handle);
        return 0;
    }
    return handle;
}

void Program::apply()
{
    glUseProgram(_program);
}