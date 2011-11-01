//
//  ShaderManager.cpp
//  angry_bus
//
//  Created by suning on 11-10-31.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#include "ShaderManager.h"
#include "Shader.h"
ShaderManager::ShaderManager()
{
    
}

ShaderManager::~ShaderManager()
{
    NameShaderMap::iterator it = _shaders.begin();
    for (; it != _shaders.end(); ++it)
    {
        Shader* s = it->second;
        delete s;
        s = 0;
    }
    _shaders.clear();
}

Shader* ShaderManager::createShader(std::string const &name)
{
    NameShaderMap::iterator it = _shaders.find(name);
    if (it == _shaders.end())
    {
        _shaders[name] = new Shader;
        _shaders[name]->setName(name);
    }
    
    return _shaders[name];
}

Shader* ShaderManager::getShader(std::string const &name)
{
    NameShaderMap::iterator it = _shaders.find(name);
    if (it == _shaders.end())
    {
        return NULL;
    }
    
    return _shaders[name];
}

Shader* ShaderManager::createAndBuildShader(const std::string& name, const std::string& file, unsigned int shaderType)
{
    Shader* s = createShader(name);
    s->setFile(file);
    s->setType(shaderType);
    s->build();
    return s;
}
