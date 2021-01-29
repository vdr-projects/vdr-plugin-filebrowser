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

#ifndef FILEBROWSER_MENU_THREADS_H
#define FILEBROWSER_MENU_THREADS_H
 
#include <vdr/osdbase.h>
#include <vdr/status.h>
#include "statebag.h"
#include "threads.h"

class cOsdMenuThreadList : public cOsdMenu, public cStatus
{
  protected:
    cFilebrowserStatebag* Statebag;
  public:
    cOsdMenuThreadList(cFilebrowserStatebag* Statebag);
    eOSState ProcessKey(eKeys Key);
    void UpdateHelp();
    void UpdateMenuItem(cOsdItem *Item, cCommandThread *Thread);
    void OsdCurrentItem(const char *Text);
};

#endif
