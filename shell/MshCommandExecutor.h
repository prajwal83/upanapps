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
#pragma once

#include <ctype.h>
#include <ustring.h>
#include <map.h>

class MshCommand;

class MshCommandExecutor {
private:
  MshCommandExecutor();

public:
  static MshCommandExecutor& Instance() {
    static MshCommandExecutor cmdExecutor;
    return cmdExecutor;
  }

  typedef upan::map<upan::string, MshCommand*> CmdMap;
  const CmdMap& getCommands() {
    return _commands;
  }

  bool executeInternalCommand();
  bool executeProcess();

private:
  CmdMap _commands;
};
