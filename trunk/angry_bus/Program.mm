//
//  Program.cpp
//  angry_bus
//
//  Created by suning on 11-10-29.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//
#include "Program.h"
#include "Shader.h"
#include "ShaderManager.h"
#import <QuartzCore/QuartzCore.h>

Program::Program()
:_program(0)
{
    
}

Program::~Program()
{
    glDeleteProgram(_program);
}

void Program::setVertexShader(const std::string& vs)
{
    _vsName = vs;
}

void Program::setFragmentShader(const std::string& fs)
{
    _fsName = fs;
}

bool Program::build()
{
    Shader* vs = ShaderManager::getInstancePtr()->getShader(_vsName);
    Shader* fs = ShaderManager::getInstancePtr()->getShader(_fsName);
    _program = glCreateProgram();
    glAttachShader(_program, vs->getID());
    glAttachShader(_program, fs->getID());
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

void Program::apply()
{
    glUseProgram(_program);
}

void Program::setVertexAttributePointer(unsigned int index,
					unsigned int  size,
					unsigned int  type,
					bool  normalized,
					int  stride,
					const void*  pointer)
{
    glVertexAttribPointer(index, size, type, normalized, stride, pointer);
    glEnableVertexAttribArray(index);
}
void Program::setVertexAttributePointer(std::string attributeName,
					unsigned int  size,
					unsigned int  type,
					bool  normalized,
					int  stride,
					const void*  pointer)
{
    unsigned int index = glGetAttribLocation(_program, attributeName.c_str());
    setVertexAttributePointer(index, size, type, normalized, stride, pointer);
}

