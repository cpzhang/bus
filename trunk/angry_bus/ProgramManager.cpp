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