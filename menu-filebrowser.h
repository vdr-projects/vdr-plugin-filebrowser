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

#ifndef FILEBROWSER_MENU_H
#define FILEBROWSER_MENU_H

#include <vdr/osdbase.h>
#include <vdr/status.h>
#include <vdr/keys.h>
#include <vdr/menuitems.h>
#include <vdr/tools.h>
#include "statebag.h"

/**
  *@author Holger Brunn
  */

// Forward declarations for commands.h
class cFilebrowserCommandContainer;
class cFilebrowserDestinationContainerCommand;

enum eMenuFilebrowserTask {taskBrowse, taskSelectDestination, taskRequireAccessCode, taskGetUserInput};

enum eFilebrowserOSStates
{
  osFilebrowserCloseRefresh = osUser1,
  osFilebrowserCloseExec = osUser2,
  osFilebrowserAccessCodeOk = osUser3
};

class cOsdMenuFilebrowser : public cOsdMenu, public cStatus
{
  friend class cFilebrowserMarkCommand;
  friend class cFilebrowserMarkAllCommand;
  friend class cFilebrowserUnmarkCommand;
  friend class cFilebrowserUnmarkAllCommand;
  friend class cFilebrowserCommandThreadList;
  friend class cFilebrowserCommandSourcesList;
  friend class cFilebrowserCommandOtherCommands;
  friend class cFilebrowserDestinationContainerCommand;
  friend class cFilebrowserDestinationAbortCommand;
  friend class cFilebrowserDestinationNewCommand;

  protected:
    cFilebrowserStatebag* Statebag;

    cFilebrowserCommands* ActualCommands;
    cFilebrowserCommandContainer* LeftVisibleCommand;

    cFilebrowserDestinationContainerCommand* DestinationContainerCommand;

    char* BaseDirectory;

    void LoadDir(cString Directory);
    void Refresh(const char* CurrentFile=NULL);
    void UpdateHelp();

    char* CurrentFilename();

    eMenuFilebrowserTask Task;

    static int DirectorySort(const dirent64** File1, const dirent64** File2);
    /*
     *  This filters entries shown in Filebrowser
     *  The function uses Statebag->ShowHiddenFiles and Statebag->Filter
     *  Override it to have a custom filter if those are not enough
     */
    virtual bool MatchesFilter(dirent64* Entry);

    void UpdateCommands(const char* Filename, bool IsVirtualNewFile, bool NewFileInEditMode);

  public:
    cOsdMenuFilebrowser(char* Directory, cFilebrowserStatebag* Statebag);
    ~cOsdMenuFilebrowser();
    virtual eOSState ProcessKey(eKeys Key);
    /* cStatus */
    void OsdCurrentItem(const char *Text);
};

class cOsdItemFileEntry : public cOsdItem
{
  protected:
    char* Filename;
    char* Name;
    bool IsParentDir;
    bool Marked;
    cOsdItemFileEntry() {};

    void UpdateText();
  public:
    cOsdItemFileEntry(dirent64* DirectoryEntry, cString Directory, cFilebrowserStatebag* Statebag);
    ~cOsdItemFileEntry();
    virtual eOSState ProcessKey(eKeys Key);
    bool IsDir();
    bool IsParentDirectory() { return IsParentDir; };
    bool IsMarked() { return Marked; };
    char* GetFilename() { return Filename; };
    void Mark(bool Marked);
};

class cOsdItemNewFileEntry : public cMenuEditStrItem
{
  protected:
    char* Directory;
    char* Name;
    char* Filename;
    
  public:
    cOsdItemNewFileEntry(char* Value, cString Directory);
    ~cOsdItemNewFileEntry();
    eOSState ProcessKey(eKeys Key);
    char* GetFilename();
    bool InEditMode();
};


#endif
