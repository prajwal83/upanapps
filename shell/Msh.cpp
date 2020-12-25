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
# include <Msh.h>
# include <CommandLineParser.h>
# include <MshCommands.h>
//# include <SysCall.h>
# include <kb.h>
# include <string.h>
# include <stdio.h>
# include <malloc.h>
# include <fs.h>
# include <cdisplay.h>
# include <mosstd.h>

char Msh_PROMPT[10] ;
char Msh_commandLine[COMMAND_LINE_SIZE] ;
unsigned int Msh_currentCommandPos;

void Msh_Initialize()
{
	strcpy(Msh_PROMPT, "\nmsh:") ;
	Msh_currentCommandPos = 0 ;
	MshCommands_Init() ;
}

void Msh_DisplayCommandPrompt()
{
	char* szPWD ;
	getpwd(&szPWD) ;
	printf("%s%s> ", Msh_PROMPT, szPWD) ;
	free(szPWD) ;
}

void Msh_ClearCommandLine()
{
	memset(Msh_commandLine, 0, COMMAND_LINE_SIZE) ;
}

void Msh_ProcessCommandLine()
{
	Msh_commandLine[Msh_currentCommandPos] = '\0' ;
	Msh_currentCommandPos = 0 ;
	CommandLineParser_Parse(Msh_commandLine) ;

	if(CommandLineParser_GetNoOfCommandLineEntries() != 0)
	{
		if(!MshCommands_ExecuteInternalCommand())
		{
			if(!MshCommands_ExecuteProcess())
			{
				puts("\n No Such Command or Execuable") ;
			}
		}
	}

	Msh_ClearCommandLine() ;
}

void Msh_Start()
{
	char ch ;

	puts("\n\n Welcome to Mos Shell") ;

	Msh_DisplayCommandPrompt() ;

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
				if(Msh_currentCommandPos > 0)
				{
					Msh_currentCommandPos-- ;
					int x = Msh_commandLine[Msh_currentCommandPos] == '\t' ? 4 : 1 ;
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
				Msh_ProcessCommandLine() ;
				Msh_DisplayCommandPrompt() ;
				break ;

			default:

				if(Msh_currentCommandPos < COMMAND_LINE_SIZE)
				{
					putc(ch, stdout) ;
					Msh_commandLine[Msh_currentCommandPos++] = ch ;
				}
		}
	}
}
