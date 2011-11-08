#ifndef _ProgramManager_
#define _ProgramManager_
#include <string>
#include <map>
#include "Singleton.h"
class Program;
class ProgramManager : public Singleton<ProgramManager>
{
public:
    ProgramManager();
    ~ProgramManager();
    
    Program* createProgram(const std::string& name);
    Program* getProgram(const std::string& name);
    Program* createAndBuildProgram(const std::string& name, const std::string& vsName, const std::string& fsName);
private:
    typedef std::map<std::string, Program*> NameProgramMap;
    NameProgramMap    _programs;
};

#endif
