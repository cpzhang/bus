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
    enum eShaderType
    {
	eShaderType_Fragment = 0x8B30,
	eShaderType_Vertex = 0x8B31,
    };
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
