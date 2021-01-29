/*  This file is part of vdr-filebrowser.

    vdr-filebrowser is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    vdr-filebrowser is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef FILEBROWSER_COMMAND_OTHER_H
#define FILEBROWSER_COMMAND_OTHER_H

#include <vdr/osdbase.h>
#include "commands.h"
#include "statebag.h"

/**
@author Holger Brunn
*/

class cFilebrowserCommandOtherCommands : public cFilebrowserCommand
{
  protected:
    cFilebrowserCommands* Commands;
  public:
    cFilebrowserCommandOtherCommands(cFilebrowserStatebag* Statebag);
    ~cFilebrowserCommandOtherCommands();
    bool Execute(cOsdMenu* Menu, char* DestinationFile, char* CurrentFile);
    bool Matches(const char* Filename);
};

class cOsdMenuOtherCommands : public cOsdMenu
{
  protected:
    cFilebrowserCommands* Commands;
    cFilebrowserCommands* RunCommands;
  public:
    cOsdMenuOtherCommands(cFilebrowserCommands* Commands, char* CurrentFile, cFilebrowserCommands* RunCommands);
    ~cOsdMenuOtherCommands();
    eOSState ProcessKey(eKeys Key);
};

#endif
