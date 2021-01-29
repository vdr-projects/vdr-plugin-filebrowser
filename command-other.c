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

#include "command-other.h"
#include "menu-filebrowser.h"
#include "tools.h"

cFilebrowserCommandOtherCommands::cFilebrowserCommandOtherCommands(cFilebrowserStatebag* Statebag) : cFilebrowserCommand(Statebag)
{
  Name=strdup(tr("Other"));
  cConfigReader Reader=cConfigReader(Statebag, "othercommands.conf");
  char* Line=NULL;
  Commands=new cFilebrowserCommands();
  while((Line=Reader.Read()))
  {
    D(fprintf(stderr, "Searching %s in Commands\n", Line));
    cFilebrowserCommandContainer* Command=Statebag->GetCommands()->First();
    while(Command)
    {
      if(strcmp(Command->GetObject()->GetName(), tr(Line))==0)
      {
        cFilebrowserCommandContainer* Dummy=Command->Next();
        Statebag->GetCommands()->Del(Command, false);
        Commands->Add(Command);
        Command=Dummy;
        D(fprintf(stderr, "Found %s in Commands\n", Line));
      }
      else
      {
        Command=Command->Next();
      }
    }
  }
}

cFilebrowserCommandOtherCommands::~cFilebrowserCommandOtherCommands()
{
  if(Commands) delete Commands;
}

bool cFilebrowserCommandOtherCommands::Execute(cOsdMenu* Menu, char* DestinationFile, char* CurrentFile)
{
  cOsdMenuFilebrowser* FilebrowserMenu=(cOsdMenuFilebrowser*)Menu;
  FilebrowserMenu->AddSubMenu(new cOsdMenuOtherCommands(Commands, CurrentFile, FilebrowserMenu->ActualCommands));
  return true;
}
    
bool cFilebrowserCommandOtherCommands::Matches(const char* Filename)
{
  return true;
}

cOsdMenuOtherCommands::cOsdMenuOtherCommands(cFilebrowserCommands* Commands, char* CurrentFile, cFilebrowserCommands* RunCommands) : cOsdMenu(tr("Other Commands"))
{
  this->Commands=new cFilebrowserCommands();
  this->RunCommands=RunCommands;
  SetHasHotkeys();
  for(cFilebrowserCommandContainer* Command=Commands->First(); Command; Command=Command->Next())
  {
    if(Command->GetObject()->Matches(CurrentFile))
    {
      Add(new cOsdItem(hk(Command->GetObject()->GetName()), (eOSState)osFilebrowserCloseExec));
      this->Commands->Add(new cFilebrowserCommandContainer(Command->GetObject(), false));
    }
  }
}

cOsdMenuOtherCommands::~cOsdMenuOtherCommands()
{}

eOSState cOsdMenuOtherCommands::ProcessKey(eKeys Key)
{
  eOSState State=cOsdMenu::ProcessKey(Key);
  if(State==(eOSState)osFilebrowserCloseExec)
  {
    RunCommands->Clear();
    RunCommands->Add(new cFilebrowserCommandContainer(Commands->Get(Current())->GetObject(), false));
  }
  switch(Key)
  {
    case kGreen:
    case kRed:
    case kBlue:
    case kYellow:
      State=osContinue;
      break;
    default:
      break;
  }
  return State;
}


