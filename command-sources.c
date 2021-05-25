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

#include "command-sources.h"
#include "menu-setup.h"

/*
  Implementation of cFilebrowserCommandSourcesList
*/

cFilebrowserCommandSourcesList::cFilebrowserCommandSourcesList(cFilebrowserStatebag* Statebag) : cFilebrowserCommand(Statebag)
{
  Name=strcpyrealloc(Name, trNOOP("Sources"));
  Sources=new cSourcesList();

  cConfigReader SourcesReader=cConfigReader(Statebag, "sources.conf");
  char* Line=NULL;
  while((Line=SourcesReader.Read()))
  {
    Sources->Add(new cSource(Line));
  }
}

cFilebrowserCommandSourcesList::~cFilebrowserCommandSourcesList()
{
  if(Sources) delete(Sources);
}

bool cFilebrowserCommandSourcesList::Execute(cOsdMenu* Menu, char* DestinationFile, char* SelectedFile)
{
  cOsdMenuFilebrowser* FbMenu=(cOsdMenuFilebrowser*)Menu;
  cOsdMenuSourcesList* List=new cOsdMenuSourcesList(Statebag, Sources);
  for(cSource* Source=Sources->First(); Source; Source=Sources->Next(Source))
  {
    List->Add(new cOsdItemSource(Statebag, Source));
  }
  FbMenu->AddSubMenu(List);
  return true;
}

bool cFilebrowserCommandSourcesList::Matches(const char* Filename)
{
  return true;
}

/*
  Implementation of cFilebrowserCommandSourcesList::cSource
*/

cFilebrowserCommandSourcesList::cSource::cSource(char* Line)
{
  cConfigParser Parser=cConfigParser(Line);
  for(char* Text=Parser.First(); Text; Text=Parser.Next())
  {
    switch(Parser.GetFieldNumber())
    {
      case 0:
        Name=Text;
        break;
      case 1:
        Path=Text;
        break;
      case 2:
        Filter=Text;
        break;
    }

  }
  D(fprintf(stderr, "[filebrowser] New source: \"%s\" in \"%s\" [%s]\n", *Name, *Path, *Filter));

  if(!*Name || !*Path)
  {
    D(fprintf(stderr, "[filebrowser] Misconfigured sources.conf: \"%s\"!\n", Line));
    esyslog("[filebrowser] Misconfigured sources.conf: \"%s\"!\n", Line);
    Name=*Name ? Name : "Error!";
    Path=*Path ? Path : "/";
  }
}

void cFilebrowserCommandSourcesList::cSource::SwitchTo(cFilebrowserStatebag* Statebag)
{
  D(fprintf(stderr, "[filebrowser] Setting new source: %s\n", *Path));
  sprintf(Statebag->BaseDir, "%s", Path);
  Statebag->CurrentFiles->Clear();
  Statebag->CurrentDirectory=Path;
  Statebag->Filter=Filter;
  Statebag->FilebrowserPlugin->SetupStore(SETUP_PARAM_BASEDIR, Path);
  Statebag->FilebrowserPlugin->SetupStore(SETUP_PARAM_FILTER, Filter);
}

/*
  Implementation of cOsdMenuSourcesList
*/

cOsdMenuSourcesList::cOsdMenuSourcesList(cFilebrowserStatebag* Statebag, cFilebrowserCommandSourcesList::cSourcesList* Sources) : cOsdMenu(tr("Sources"))
{
  this->Statebag=Statebag;
  this->Sources=Sources;
}


cOsdMenuSourcesList::~cOsdMenuSourcesList()
{}

/*
  Implementation of cOsdItemSource
*/

cOsdItemSource::cOsdItemSource(cFilebrowserStatebag* Statebag, cFilebrowserCommandSourcesList::cSource* Source)
{
  this->Statebag=Statebag;
  this->Source=Source;
  SetText(Source->Name);
}

eOSState cOsdItemSource::ProcessKey(eKeys Key)
{
  if(Key==kOk)
  {
    Source->SwitchTo(Statebag);
    return (eOSState)osFilebrowserCloseRefresh;
  }
  else
  {
    return cOsdItem::ProcessKey(Key);
  }
}

