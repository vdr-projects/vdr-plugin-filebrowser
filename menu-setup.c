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

#include <strings.h>
#include "menu-setup.h"
#define MAX(a,b) ((a) > (b) ? (a) : (b))

cFilebrowserSetupPage::cFilebrowserSetupPage(cFilebrowserStatebag* Statebag) : cMenuSetupPage()
{
  this->Statebag=Statebag;
  NewShowHiddenFiles=Statebag->ShowHiddenFiles;
  NewShowFullPath=Statebag->ShowFullPath;
  Add(new cMenuEditBoolItem(tr("Show hidden files"), &NewShowHiddenFiles));
  Add(new cMenuEditBoolItem(tr("Show full path in title"), &NewShowFullPath));
}

cFilebrowserSetupPage::~cFilebrowserSetupPage()
{
}

void cFilebrowserSetupPage::Store()
{
  SetupStore(SETUP_PARAM_SHOW_HIDDEN_FILES, Statebag->ShowHiddenFiles = NewShowHiddenFiles);
  SetupStore(SETUP_PARAM_SHOW_FULL_PATH, Statebag->ShowFullPath = NewShowFullPath);
}

