//
//  Shader.h
//  angry_bus
//
//  Created by suning on 11-10-31.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//
#ifndef _Shader_
#define _Shader_
#include <string>
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
class Shader
{
public:
    Shader();
    ~Shader();
    
    void setFile(const std::string& fileName);
    void setName(const std::string& name);
    std::string getName();
    void setType(GLenum  shaderType);
    bool build();
    GLuint getID();
private:
    GLuint  _shader;
    GLenum  _type;
    std::string _fileName;
    std::string _name;
};
#endif