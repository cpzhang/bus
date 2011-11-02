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
	glGetProgramiv(_shader, GL_INFO_LOG_STATUS, &infoLen);
	if(infoLen > 0)
	{
	    static char sError[512];
	    glGetProgramInfoLog(_shader, infoLen, NULL, sError);
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
// GLint glGetUniformLocation(GLuint program, const char* name)
    unsigned int index = glGetAttribLocation(_program, attributeName.c_str());
    setVertexAttributePointer(index, size, type, normalized, stride, pointer);
}

