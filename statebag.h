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

#ifndef FILEBROWSER_STATEBAG_H
#define FILEBROWSER_STATEBAG_H

#include <vdr/tools.h>
#include <vdr/plugin.h>

//Forward declarations for used classes
class cStringContainerList;
#ifdef FILEBROWSER_PLUGIN_BUILD
class cThreadList;
#endif
class cFilebrowserCommands;

class cFilebrowserStatebag
{
  protected:
    cStringContainerList* SelectedFiles;
#ifdef FILEBROWSER_PLUGIN_BUILD
    cThreadList* Threads;
#endif
    cFilebrowserCommands* Commands;

  public:
    cFilebrowserStatebag();
    ~cFilebrowserStatebag();

    cStringContainerList* GetSelectedFiles() { return SelectedFiles; };
#ifdef FILEBROWSER_PLUGIN_BUILD
    cThreadList* GetThreads() { return Threads; };
#endif
    cFilebrowserCommands* GetCommands() { return Commands; };

    char BaseDir[_POSIX_PATH_MAX];
    bool ShowHiddenFiles;
    bool ShowFullPath;
    
    cString Filter;
    cString CurrentDirectory;
    cString ConfigDirectory;
    
    cStringContainerList* CurrentFiles;
    cString UserInput;
    cString UserInputPassword;

#ifdef FILEBROWSER_PLUGIN_BUILD
    /*
    Is an update requested by some thread?
    */
    bool UpdateRequested;

    cPlugin* FilebrowserPlugin;
#endif
};

#endif
