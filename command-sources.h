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
#ifndef FILEBROWSER_COMMAND_SOURCES_H
#define FILEBROWSER_COMMAND_SOURCES_H

#include <vdr/osdbase.h>
#include <vdr/tools.h>
#include "statebag.h"
#include "commands.h"

class cFilebrowserCommandSourcesList : public cFilebrowserCommand
{
  public:
    class cSource : public cListObject
    {
      public:
        cSource(char* Line);
        cString Name;
        cString Path;
        cString Filter;
        void SwitchTo(cFilebrowserStatebag* Statebag);
    };
    class cSourcesList : public cList<cSource> {};
  protected:
    cSourcesList* Sources;
  public:
    cFilebrowserCommandSourcesList(cFilebrowserStatebag* Statebag);
    ~cFilebrowserCommandSourcesList();
    bool Execute(cOsdMenu* Menu, char* DestinationFile, char* SelectedFile);
    bool Matches(const char* Filename);
};

class cOsdMenuSourcesList : public cOsdMenu
{
  protected:
    cFilebrowserStatebag* Statebag;
    cFilebrowserCommandSourcesList::cSourcesList* Sources;
  
  public:
    cOsdMenuSourcesList(cFilebrowserStatebag* Statebag, cFilebrowserCommandSourcesList::cSourcesList* Sources);

    ~cOsdMenuSourcesList();

};

class cOsdItemSource : public cOsdItem
{
  protected:
    cFilebrowserCommandSourcesList::cSource* Source;
    cFilebrowserStatebag* Statebag;

  public:
    cOsdItemSource(cFilebrowserStatebag* Statebag, cFilebrowserCommandSourcesList::cSource* Source);
    eOSState ProcessKey(eKeys Key);
};

#endif
