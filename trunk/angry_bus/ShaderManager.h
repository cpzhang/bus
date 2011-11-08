#ifndef _ShaderManager_
#define _ShaderManager_
#include <string>
#include <map>
#include "Singleton.h"
class Shader;
class ShaderManager : public Singleton<ShaderManager>
{
public:
    ShaderManager();
    ~ShaderManager();
    
    Shader* createShader(const std::string& name);
    Shader* createAndBuildShader(const std::string& name, const std::string& file, unsigned int shaderType);
    Shader* getShader(const std::string& name);
private:
    typedef std::map<std::string, Shader*> NameShaderMap;
    NameShaderMap   _shaders;
};
#endif
