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

#ifndef FILEBROWSER_SETUP_H
#define FILEBROWSER_SETUP_H

#include <vdr/menuitems.h>
#include "statebag.h"

#define SETUP_PARAM_BASEDIR "BaseDir"
#define SETUP_PARAM_FILTER "Filter"
#define SETUP_PARAM_SHOW_HIDDEN_FILES "ShowHiddenFiles"
#define SETUP_PARAM_SHOW_FULL_PATH "ShowFullPath"

class cFilebrowserSetupPage : public cMenuSetupPage
{
  protected:
    int NewShowHiddenFiles;
    int NewShowFullPath;
    cFilebrowserStatebag* Statebag;
  
  public:
    cFilebrowserSetupPage(cFilebrowserStatebag* Statebag);
    ~cFilebrowserSetupPage();

    virtual void Store(void);
};

#endif
