/*
 *  Upanix - An x86 based Operating System
 *  Copyright (C) 2011 'Prajwala Prabhakar' 'srinivasa_prajwal@yahoo.co.in'
 *                                                                          
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *                                                                          
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *                                                                          
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/
 */
# include <MshCommands.h>
# include <MshCommandExecutor.h>
# include <Msh.h>
# include <mosstd.h>
# include <malloc.h>

MshCommandExecutor::MshCommandExecutor(const upan::string& cmdLine) : _cmd(upan::option<MshCommand*>::empty()) {
  parse(cmdLine);
  _cmdName = _cmdLineTokens.empty() ? "" : _cmdLineTokens[0];
  auto it = Msh::Instance().getCommands().find(_cmdName);
  if (it != Msh::Instance().getCommands().end()) {
    _cmd = upan::option<MshCommand*>(it->second);
  }
}

static bool CommandLineParser_TokenCompare(char ch) {
  return iswhitespace(ch) ;
}

static bool CommandLineParser_GroupToken(char ch) {
  return (int) (ch == '"') ;
}

static void CommandLineParser_Copy(int index, const char* src, int len, void* context) {
  MshCommandExecutor* c = reinterpret_cast<MshCommandExecutor*>(context);
  c->addCmdToken(upan::string(src, len));
}

void MshCommandExecutor::parse(const upan::string& cmdLine) {
  int tokenCount;
  strtok_c(cmdLine.c_str(),
           &CommandLineParser_TokenCompare,
           &CommandLineParser_GroupToken,
           &CommandLineParser_Copy,
           &tokenCount,
           this);

  expandCmdLine();

  for(int i = 1; i < _cmdLineTokens.size(); ++i) {
    const auto& token = _cmdLineTokens[i];
    if (token.length()) {
      if (token[0] == '-') {
        _options.insert(token);
      } else {
        _params.push_back(token);
      }
    }
  }
}

void MshCommandExecutor::expandCmdLine() {
  for(auto& token : _cmdLineTokens) {
    if (token.length() > 1) {
      if(token[0] == '$' && !iswhitespace(token[1]))
      {
        int j ;
        for(j = 0; token[j] != '\0' && !iswhitespace(token[j]) && token[j] != '/'; j++) ;

        const upan::string temp(token.c_str() + j);
        char* val = getenv(upan::string(token.c_str() + 1, j - 1).c_str());
        token = val == NULL ? "" : val;
        token += temp;
      }
    }
  }
}

void MshCommandExecutor::execute() {
  if (_cmd.isEmpty()) {
    if (!executeProcess()) {
      puts("\n No Such Command or Execuable") ;
    }
  } else {
    executeInternalCommand(*_cmd.value());
  }
}

void MshCommandExecutor::executeInternalCommand(MshCommand& cmd) {
  const int noOfParams = _params.size();
  if (noOfParams < cmd.minParamCount() || noOfParams > cmd.maxParamCount()) {
    cmd.printUsage();
  } else {
    cmd.execute(*this);
  }
}

bool MshCommandExecutor::executeProcess() {
  char** argv = (char**)malloc(sizeof(char*) * _cmdLineTokens.size());
  for(int i = 0; i < _cmdLineTokens.size(); ++i) {
    argv[i] = _cmdLineTokens[i].c_str();
  }

	const int pid = execv(_cmdName.c_str(), _cmdLineTokens.size(), argv) ;

  free(argv);

	/* --> way to work using execvp */
	/*
	char** argv = CommandLineParser_GetArgV();
	argv[CommandLineParser_GetNoOfCommandLineEntries()] = (char*)NULL ;
	pid = execvp(CommandLineParser_GetCommand(), argv );
	*/
	
	if(pid < 0) {
		return false ;
	} else {
		waitpid(pid) ;
	}
	return true ;
}