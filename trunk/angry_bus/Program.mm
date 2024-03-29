#include "Program.h"
#include "Shader.h"
#include "ShaderManager.h"
#import <QuartzCore/QuartzCore.h>
#include <iostream>
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
    if(!vs) return false;
    Shader* fs = ShaderManager::getInstancePtr()->getShader(_fsName);
    if(!fs) return false;
    _program = glCreateProgram();
    if(!_program) return false;
    glAttachShader(_program, vs->getID());
    glAttachShader(_program, fs->getID());
    glLinkProgram(_program);
    GLint status;
    glGetProgramiv(_program, GL_LINK_STATUS, &status);
    if (!status)
    {
	GLint infoLen = 0;
	glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &infoLen);
	if(infoLen > 0)
	{
	    static char sError[512];
	    glGetProgramInfoLog(_program, infoLen, NULL, sError);
	    std::cout<<"build program failed! hint: "<<sError<<std::endl;
	}
        return false;
    }

    return true;
}

void Program::apply()
{
    glUseProgram(_program);
}

void Program::setVertexAttribf(const std::string& attributeName, float x, float y, float z, float w)
{
    unsigned int index = glGetAttribLocation(_program, attributeName.c_str());
    glVertexAttrib4f(index, x, y, z, w);
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
void Program::setVertexAttributePointer(const std::string& attributeName,
					unsigned int  size,
					unsigned int  type,
					bool  normalized,
					int  stride,
					const void*  pointer)
{
// GLint glGetUniformLocation(GLuint program, const char* name)
    unsigned int index = glGetAttribLocation(_program, attributeName.c_str());
    setVertexAttributePointer(index, size, type, normalized, stride, pointer);
}

int Program::getMaxVertexAttributesNumber()
{
    GLint n;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &n);
    return n;
}

void Program::setUniformi(const std::string& uniformName, int value)
{
    int index = glGetUniformLocation(_program, uniformName.c_str());
    glUniform1i(index, value);
}

void Program::setUniformf(const std::string& uniformName, float value)
{
    int index = glGetUniformLocation(_program, uniformName.c_str());
    glUniform1f(index, value);
}

void Program::setUniformf(const std::string& uniformName, float x, float y, float z)
{
    int index = glGetUniformLocation(_program, uniformName.c_str());
    glUniform3f(index, x, y, z);

}
void Program::setUniformf(const std::string& uniformName, float x, float y, float z, float w)
{
    int index = glGetUniformLocation(_program, uniformName.c_str());
    glUniform4f(index, x, y, z, w);
}

void Program::setUniformMatrixfv(const std::string& uniformName, unsigned int count, bool transpose, const float* value)
{
    int index = glGetUniformLocation(_program, uniformName.c_str());
    glUniformMatrix4fv(index, count, transpose, value);
}

void Program::enableVertexAttribArray(std::string const &attributeName)
{
    int index = glGetUniformLocation(_program, attributeName.c_str());
    glEnableVertexAttribArray(index);
}

void Program::disableVertexAttribArray(std::string const &attributeName)
{
    int index = glGetUniformLocation(_program, attributeName.c_str());
    glDisableVertexAttribArray(index);
}
