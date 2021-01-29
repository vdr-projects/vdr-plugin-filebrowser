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
 
#ifndef FILEBROWSER_OUTPUT_H
#define FILEBROWSER_OUTPUT_H

#include <vdr/menu.h>

//Forwarddeclaration for cCommandThreadTextOutput
class cCommandThreadTextOutput;

class cOsdMenuTextOutput : public cMenuText
{
  friend class cConfigCommandThread;

  protected:
    cCommandThreadTextOutput* Thread;
    bool Update;

    void UpdateHelp();

  public:
    cOsdMenuTextOutput(cCommandThreadTextOutput* Thread);
    ~cOsdMenuTextOutput();
    virtual void Display(void);
    virtual eOSState ProcessKey(eKeys Key);
};

#endif
