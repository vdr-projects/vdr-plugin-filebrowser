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

#include "threads.h"
#include "menu-output.h"
#include "menu-filebrowser.h"
#include <vdr/interface.h>

cOsdMenuTextOutput::cOsdMenuTextOutput(cCommandThreadTextOutput* Thread) : cMenuText("", "")
{
  this->Thread=Thread;
  Update=Thread->GetState() == tsRunning || Thread->GetState() == tsCreated;
  UpdateHelp();
}

void cOsdMenuTextOutput::Display()
{
  cMenuText::Display();
  //TODO: That's not optimal, but it doesn't hurt too much...
  /*
    Maybe propose to have CanScroll() for cSkinDisplayMenu?
  */
  Thread->Lock();
  for(char* i=Thread->OutputBuffer; *i; i++)
  {
    if(*i=='\n')
      DisplayMenu()->Scroll(false, true);
  }
  Thread->Unlock();
}

void cOsdMenuTextOutput::UpdateHelp()
{
  SetHelp("", Thread->Active() ? (Update ? tr("No Updates") : tr("Updates")) : "",
          Thread->GetState()==tsPaused ? tr("Resume") : (Thread->GetState()==tsRunning ? tr("Pause") : ""),
          this->Thread->Active() ? tr("Kill") : "");
}

eOSState cOsdMenuTextOutput::ProcessKey(eKeys Key)
{
  eOSState ReturnValue=cMenuText::ProcessKey(Key);
  /* Don't make any checks for cMenuText will alway return osContinue os osBack (for kOk) */
  switch(Key)
  {
    case kGreen:
      Update=!Update;
      UpdateHelp();
      ReturnValue=osContinue;
      break;
    case kYellow:
      switch(Thread->GetState())
      {
        case tsPaused:
          Thread->Resume();
          Update=true;
          break;
        case tsRunning:
          Thread->Pause();
          Update=false;
          break;
        default:
          //do nothing
          break;
      }
      UpdateHelp();
      ReturnValue=osContinue;
      break;
    case kBlue:
      if(Thread->Active() && Interface->Confirm(tr("Kill")))
      {
        Thread->Cancel();
        UpdateHelp();
      }
      ReturnValue=osContinue;
      break;
    case kNone:
      if(Update)
      {
        Thread->Lock();
        SetText(Thread->OutputBuffer);
        Thread->Unlock();
        Update=Thread->Active();
        UpdateHelp();
        Display();
      }
      ReturnValue=osContinue;
      break;
    case kBack:
    case kOk:
      ReturnValue=(eOSState)osFilebrowserCloseRefresh;
      break;
    default:
      break;
  }
  return ReturnValue;
}

cOsdMenuTextOutput::~cOsdMenuTextOutput()
{
}
