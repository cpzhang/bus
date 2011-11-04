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
    void disableVertexAttribArray(const std::string& attributeName);
    void enableVertexAttribArray(const std::string& attributeName);
    void setVertexAttribf(const std::string& attributeName, float x, float y, float z, float w);
    void setVertexAttributePointer(unsigned int index,
                                           unsigned int  size,
                                           unsigned int  type,
                                           bool  normalized,
                                           int  stride,
                                           const void*  pointer);
    void setVertexAttributePointer(const std::string& attributeName,
                                           unsigned int  size,
                                           unsigned int  type,
                                           bool  normalized,
                                           int  stride,
                                           const void* pointer);
    void setUniformi(const std::string& uniformName, int value);
    void setUniformf(const std::string& uniformName, float value);
    void setUniformf(const std::string& uniformName, float x, float y, float z);
    void setUniformf(const std::string& uniformName, float x, float y, float z, float w);
    void setUniformMatrixfv(const std::string& uniformName, unsigned int count, bool transpose, const float* value);
public:
    static int getMaxVertexAttributesNumber();
private:
    std::string _vsName;
    std::string _fsName;
    GLuint  _program;
};

#endif
