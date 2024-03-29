//
//  ProgramManager.cpp
//  angry_bus
//
//  Created by suning on 11-10-31.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#include "ProgramManager.h"
#include "Program.h"
ProgramManager::ProgramManager()
{
    
}

ProgramManager::~ProgramManager()
{
    NameProgramMap::iterator it = _programs.begin();
    for (; it != _programs.end(); ++it)
    {
        Program* s = it->second;
        delete s;
        s = 0;
    }
    _programs.clear();
}

Program* ProgramManager::createProgram(const std::string& name)
{
    NameProgramMap::iterator it = _programs.find(name);
    if (it == _programs.end())
    {
        _programs[name] = new Program;
    }
    
    return _programs[name];
}


Program* ProgramManager::getProgram(const std::string& name)
{
    NameProgramMap::iterator it = _programs.find(name);
    if (it == _programs.end())
    {
        return NULL;
    }
    
    return _programs[name];
}

Program* ProgramManager::createAndBuildProgram(const std::string& name, const std::string& vsName, const std::string& fsName)
{
    Program* p = createProgram(name);
    if(p)
    {
        p->setVertexShader(vsName);
        p->setFragmentShader(fsName);
        if(!p->build()) p = 0;
    }
    return p;
}
