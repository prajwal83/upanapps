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
#pragma once

#include <ustring.h>
#include <map.h>

#define COMMAND_LINE_SIZE 70

class MshCommand;

class Msh {
private:
  Msh();

public:
  static Msh& Instance() {
    static Msh msh;
    return msh;
  }
  void start();

  typedef upan::map<upan::string, MshCommand*> CmdMap;
  const CmdMap& getCommands() {
    return _commands;
  }

private:
  void displayPrompt();
  void clearCommandLine();
  void processCommandLine();

private:
  const upan::string _prompt;
  uint32_t _cmdLinePos;
  char _cmdLine[COMMAND_LINE_SIZE];
  CmdMap _commands;
};