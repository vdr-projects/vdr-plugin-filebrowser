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

#include "menu-accesscode.h"
#include "menu-filebrowser.h"
#include <vdr/menuitems.h>

cOsdMenuAccessCode::cOsdMenuAccessCode(const char* Code)
  : cOsdMenu(tr("Access code needed"), 10)
{
  this->Code=Code;
  this->CodeBuffer=(char*)malloc(strlen(Code)+1);
  this->CodeBuffer[0]='\0';
  for(int i=0; i < DisplayMenu()->MaxItems() / 2; i++)
  {
    Add(new cOsdItem("", osUnknown, false));
  }
  Add(new cMenuEditNumItem(tr("Code"), CodeBuffer, strlen(Code), true));
}

cOsdMenuAccessCode::~cOsdMenuAccessCode()
{
  if(CodeBuffer) free(CodeBuffer);
}

bool cOsdMenuAccessCode::CheckCode()
{
  return strcmp(this->Code, this->CodeBuffer) == 0;
}

eOSState cOsdMenuAccessCode::ProcessKey(eKeys Key)
{
  eOSState retval=cOsdMenu::ProcessKey(Key);
  
  switch(Key)
  {
    case kYellow:
    case kGreen:
    case kBlue:
    case kRed:
      return osContinue;
    case k0...k9:
      if(CheckCode())
      {
        return (eOSState)osFilebrowserAccessCodeOk;
      }
      break;
    case kOk:
      if(CheckCode())
      {
        return (eOSState)osFilebrowserAccessCodeOk;
      }
      else
      {
        Skins.Message(mtError, tr("Wrong code!"));
      }
      return osContinue;
    case kBack:
      return (eOSState)osFilebrowserCloseRefresh;
    default:
      return retval;
  }
  
  return retval;
}

