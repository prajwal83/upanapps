/*
 *  Mother Operating System - An x86 based Operating System
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
# include <CommandLineParser.h>
# include <MshCommandExecutor.h>
# include <mosstd.h>

MshCommandExecutor::MshCommandExecutor() {
  auto add_cmd = [&](MshCommand* cmd) {
    auto r = _commands.insert(CmdMap::value_type(cmd->name(), cmd));
    if (!r.second) {
      throw upan::exception(XLOC, "duplicate command: %s", cmd->name().c_str());
    }
  };
  add_cmd(new MshCommandEcho());
  add_cmd(new MshCommandClearScreen());
  add_cmd(new MshCommandExit());
  add_cmd(new MshCommandCreateDir());
  add_cmd(new MshCommandDeleteFile());
  add_cmd(new MshCommandListDir());
  add_cmd(new MshCommandChangeDir());
  add_cmd(new MshCommandPresentWorkingDir());
  add_cmd(new MshCommandCopyFile());
  add_cmd(new MshCommandShowFile());
  add_cmd(new MshCommandDate());
  add_cmd(new MshCommandChangeDrive());
  add_cmd(new MshCommandShowDrives());
  add_cmd(new MshCommandMountDrive());
  add_cmd(new MshCommandUnMountDrive());
  add_cmd(new MshCommandFormatDrive());
  add_cmd(new MshCommandShowCurrentDrive());
  add_cmd(new MshCommandReboot());
  add_cmd(new MshCommandHelp());
  add_cmd(new MshCommandGetProcessDetails());
  add_cmd(new MshCommandExportEvnVar());
}

bool MshCommandExecutor::executeInternalCommand() {
  const upan::string cmdName(CommandLineParser_GetCommand());
  auto it = _commands.find(cmdName);
  if (it == _commands.end()) {
    return false;
  }
  const MshCommand& cmd = *it->second;
  const int noOfParams = CommandLineParser_GetNoOfCommandLineEntries() - 1;
  if (noOfParams < cmd.minParamCount() || noOfParams > cmd.maxParamCount()) {
    cmd.printUsage();
    return false;
  }

  cmd.execute();
  return true;
}
bool MshCommandExecutor::executeProcess() {
	const int pid = execv(CommandLineParser_GetCommand(),
				CommandLineParser_GetNoOfCommandLineEntries(),
				CommandLineParser_GetArgV()) ;

	/* --> way to work using execvp */
	/*
	char** argv = CommandLineParser_GetArgV();
	argv[CommandLineParser_GetNoOfCommandLineEntries()] = (char*)NULL ;
	pid = execvp(CommandLineParser_GetCommand(), argv );
	*/
	
	if(pid < 0)
	{
		return false ;
	}
	else
	{
		waitpid(pid) ;
	}

	return true ;
}