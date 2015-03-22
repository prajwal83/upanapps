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
#ifndef _MSH_COMMANDS_H_
#define _MSH_COMMANDS_H_

# include <ctype.h>

typedef struct MshCommand MshCommand ;

typedef void cmd_func(const MshCommand* pCommand) ;

struct MshCommand
{
	char szCommand[32] ;
	cmd_func* cmdFunc ;	
	int iMinParCount ;
	int iMaxParCount ;
	char szUsage[100] ;
} ;


void MshCommands_Init() ;
boolean MshCommands_ExecuteInternalCommand() ;
boolean MshCommands_ExecuteProcess() ;

#endif
