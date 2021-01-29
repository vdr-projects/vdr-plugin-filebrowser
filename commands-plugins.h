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

#ifndef FILEBROWSER_COMMANDS_PLUGINS_H
#define FILEBROWSER_COMMANDS_PLUGINS_H

#include <vdr/tools.h>
#include "commands.h"

class cFilebrowserCommandAnyPlugin : public cFilebrowserCommand
{
  protected:
    cString Extensions;
    cString ServiceID;
    bool ServiceAvailable;
  public:
    cFilebrowserCommandAnyPlugin(const char* Name);
    bool Matches(const char* Filename);
    bool Execute(cOsdMenu* Menu, char* DestinationFile, char* CurrentFile);
};

struct MPlayerServiceData {
  int result;
  union {
    const char *filename;
  } data;
};

class cFilebrowserCommandMPlayerPlugin : public cFilebrowserCommandAnyPlugin
{
  public:
    cFilebrowserCommandMPlayerPlugin();
    bool Execute(cOsdMenu* Menu, char* DestinationFile, char* CurrentFile);
    bool Matches(const char* Filename);
};

struct MP3ServiceData {
  int result;
  union {
    const char *filename;
  } data;
};

class cFilebrowserCommandMP3Plugin : public cFilebrowserCommandAnyPlugin
{
  public:
    cFilebrowserCommandMP3Plugin();
    bool Execute(cOsdMenu* Menu, char* DestinationFile, char* CurrentFile);
    bool Matches(const char* Filename);
};

class cFilebrowserCommandImagePlugin : public cFilebrowserCommandAnyPlugin
{
  public:
    cFilebrowserCommandImagePlugin();
};

#endif
