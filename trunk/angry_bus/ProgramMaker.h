//
//  Program.h
//  angry_bus
//
//  Created by suning on 11-10-29.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//
#ifndef _ProgramMaker_
#define _ProgramMaker_

#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include <string>
class ProgramMaker
{
public:
    ProgramMaker();
    ~ProgramMaker();

    void setVertexShaderFile(const std::string& vs);
    void setFragmentShaderFile(const std::string& fs);
    GLuint getProgram();
private:
    GLuint buildShader(GLenum st, const std::string& s);
    bool buildProgram();
private:
    std::string _vsFile;
    std::string _fsFile;
    GLuint  _vs;
    GLuint  _fs;
    GLuint  _program;
};

class ShaderProgram
{
public:
    void apply();
    
private:
    GLuint  _program;
};
#endif