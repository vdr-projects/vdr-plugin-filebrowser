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

#include "statebag.h"
#include "tools.h"
#include "commands.h"
#ifdef FILEBROWSER_PLUGIN_BUILD
#include "threads.h"
#endif

cFilebrowserStatebag::cFilebrowserStatebag()
{
#ifdef FILEBROWSER_PLUGIN_BUILD
  Threads=new cThreadList();
#endif
  SelectedFiles=new cStringContainerList();
  Commands=new cFilebrowserCommands();
  BaseDir[0]='\0';
  CurrentFiles=new cStringContainerList();
}

cFilebrowserStatebag::~cFilebrowserStatebag()
{
  //this also frees objects
#ifdef FILEBROWSER_PLUGIN_BUILD
  if(Threads) delete Threads;
#endif
  if(SelectedFiles) delete SelectedFiles;
  if(Commands) delete Commands;
  if(CurrentFiles) delete CurrentFiles;
}
 
