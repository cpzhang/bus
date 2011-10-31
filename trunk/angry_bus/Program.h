//
//  Program.h
//  angry_bus
//
//  Created by suning on 11-10-29.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//
#ifndef _Program_
#define _Program_
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include <string>
class Program
{
public:
    Program();
    ~Program();

    void setVertexShader(const std::string& vs);
    void setFragmentShader(const std::string& fs);
    bool build();
    
    void apply();
private:
    std::string _vsName;
    std::string _fsName;
    GLuint  _program;
};

#endif