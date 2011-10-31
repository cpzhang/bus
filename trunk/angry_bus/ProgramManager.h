//
//  ProgramManager.h
//  angry_bus
//
//  Created by suning on 11-10-31.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//
#ifndef _ProgramManager_
#define _ProgramManager_
#include <string>
#include <map>
class Program;
class ProgramManager
{
public:
    ProgramManager();
    ~ProgramManager();
    
    Program* createProgram(const std::string& name);
    
private:
    typedef std::map<std::string, Program*> NameProgramMap;
    NameProgramMap    _programs;
};

#endif