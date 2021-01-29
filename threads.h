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

#ifndef FILEBROWSER_THREADS_H
#define FILEBROWSER_THREADS_H

#include <vdr/thread.h>
#include <vdr/tools.h>
#include <vdr/menu.h>

#include "tools.h"
#include "menu-output.h"
#include "statebag.h"

enum ThreadState
{
  tsCreated,
  tsRunning,
  tsPaused,
  tsFinished
};

class cCommandThread : public cThread
{
  protected:
    cFilebrowserStatebag* Statebag;
    char* DestinationFile;
    char* CurrentFile;
    char* Description;
    cStringContainerList* SelectedFiles;
    ThreadState State;
    bool RemoveRequested;
    cString UserInput;
    cString UserInputPassword;
  public:
    cCommandThread(cFilebrowserStatebag* Statebag, char* DestinationFile, char* CurrentFile);
    virtual ~cCommandThread();
    virtual cOsdMenu* GetMenu();
    char* GetDescription() { return Description; };
    virtual void Cancel(int WaitSeconds = 0);
    virtual void Pause();
    virtual void Resume();
    ThreadState GetState() { return State; };
    bool IsRemoveRequested() { return RemoveRequested && State==tsFinished; };
};

class cCommandThreadTextOutput : public cCommandThread
{
  friend class cOsdMenuTextOutput;

  protected:
    char* OutputBuffer;
    long OutputBufferLength;
    pid_t ChildPid;
  public:
    cCommandThreadTextOutput(cFilebrowserStatebag* Statebag, char* DestinationFile, char* CurrentFile);
    ~cCommandThreadTextOutput();
    void Action();
    virtual void Cancel(int WaitSeconds = 0);
    virtual void Pause();
    virtual void Resume();
    virtual int Execute() { return 0; };
    virtual cOsdMenu* GetMenu();
};

//Forwarddeclaration cFilebrowserConfigCommand*
class cFilebrowserConfigCommand;

class cConfigCommandThread : public cCommandThreadTextOutput
{
  protected:
    cFilebrowserConfigCommand* Command;
    static char* SelectedFilesHandler(const char* OrgString, const char* CurrentPos, const cCommandParser::cHandlerParameters* Params);
  public:
    cConfigCommandThread(cFilebrowserStatebag* Statebag, char* DestinationFile, char* CurrentFile, cFilebrowserConfigCommand* Command);
    int Execute();
    virtual cOsdMenu* GetMenu();
};

class cThreadContainer : public cListContainer<cCommandThread>
{
  public:
    cThreadContainer(cCommandThread* Object) : cListContainer<cCommandThread>(Object) {};
};

class cThreadList : public cList<cThreadContainer> {};

#endif
