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
# include <kb.h>
# include <string.h>
# include <stdio.h>
# include <malloc.h>
# include <fs.h>
# include <cdisplay.h>
# include <mosstd.h>
# include <Msh.h>
# include <MshCommandExecutor.h>
# include <MshCommands.h>

Msh::Msh() : _prompt("msh:"), _cmdLinePos(0) {
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

void Msh::displayPrompt() {
  char* szPWD ;
  getpwd(&szPWD) ;
  printf("\n%s%s> ", _prompt.c_str(), szPWD) ;
  free(szPWD) ;
}

void Msh::clearCommandLine() {
	memset(_cmdLine, 0, COMMAND_LINE_SIZE) ;
}

void Msh::processCommandLine() {
  _cmdLine[_cmdLinePos] = '\0';
  _cmdLinePos = 0;
  MshCommandExecutor cmdExec(_cmdLine);
  cmdExec.execute();
	clearCommandLine() ;
}

void Msh::start()
{
	char ch ;

	puts("\n\n Welcome to Mos Shell") ;

  displayPrompt() ;

	while(1)
	{
		kb_get_ch_wait((int*)&ch) ;
		
		switch(ch)
		{	
			case Keyboard_LEFT_ALT:
			case Keyboard_LEFT_CTRL:
			case Keyboard_F1:
			case Keyboard_F2:
			case Keyboard_F3:
			case Keyboard_F4:
			case Keyboard_F5:
			case Keyboard_F6:
			case Keyboard_F7:
			case Keyboard_F8:
			case Keyboard_F9:
			case Keyboard_F10:
				break ;
				
			case Keyboard_CAPS_LOCK:
				break ;

			case Keyboard_BACKSPACE:
				if(_cmdLinePos > 0)	{
					_cmdLinePos-- ;
					int x = _cmdLine[_cmdLinePos] == '\t' ? 4 : 1 ;
					movcursor(-x) ;
					clrline(Display_CURSOR_CUR) ;
				}
				break ;
				
			case Keyboard_LEFT_SHIFT:
			case Keyboard_RIGHT_SHIFT:
				break ;
				
			case Keyboard_ESC:
				break ;

			case Keyboard_ENTER:
				putc('\n', stdout) ;
        processCommandLine() ;
				displayPrompt();
				break ;

			default:
				if(_cmdLinePos < COMMAND_LINE_SIZE) {
					putc(ch, stdout) ;
          _cmdLine[_cmdLinePos++] = ch ;
				}
		}
	}
}
