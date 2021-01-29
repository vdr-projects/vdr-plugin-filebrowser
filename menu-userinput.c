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

#include "menu-userinput.h"
#include "menu-filebrowser.h"

#define MAX_INPUT_LENGTH 100

cOsdMenuUserInput::cOsdMenuUserInput ( cString* UserInput, cString* UserInputPassword )
      : cOsdMenu ( tr ( "The command has requested additional input" ), 10 )
{
   if ( UserInput )
   {
      this->UserInput=UserInput;
      *UserInput=cString ( ( const char* ) malloc ( MAX_INPUT_LENGTH ), true );
      strcpy ( ( char* ) ( const char* ) *UserInput, "" );
   }

   if ( UserInputPassword )
   {
      this->UserInputPassword=UserInputPassword;
      *UserInputPassword=cString ( ( const char* ) malloc ( MAX_INPUT_LENGTH ), true );
      strcpy ( ( char* ) ( const char* ) *UserInputPassword, "" );
   }

   for ( int i=0; i < DisplayMenu()->MaxItems() / 2 - ( UserInput ? 1 : 0 ) - ( UserInputPassword ? 1 : 0 ); i++ )
   {
      Add ( new cOsdItem ( "", osUnknown, false ) );
   }

   Add ( new cOsdItem ( tr ( "The command has requested additional input" ), osUnknown, false ) );

   if ( UserInput )
   {
      Add ( new cMenuEditStrItem ( tr ( "Input" ), ( char* ) ( const char* ) *UserInput, MAX_INPUT_LENGTH ) );
   }

   if ( UserInputPassword )
   {
      Add ( new cMenuEditStrItemBlind ( tr ( "Password" ), ( char* ) ( const char* ) *UserInputPassword, MAX_INPUT_LENGTH ) );
   }
}

eOSState cOsdMenuUserInput::ProcessKey ( eKeys Key )
{
   eOSState retval=cOsdMenu::ProcessKey ( Key );

   if ( retval!=osUnknown && Key!=kBack )
   {
      return retval;
   }

   switch ( Key )
   {
      case kYellow:
      case kGreen:
      case kBlue:
      case kRed:
         return osContinue;
      case kOk:
         return ( eOSState ) osFilebrowserCloseExec;
      case kBack:
         return ( eOSState ) osFilebrowserCloseRefresh;
      default:
         return retval;
   }

   return retval;
}

cMenuEditStrItemBlind::cMenuEditStrItemBlind ( const char *Name, char *Value, int Length, const char *Allowed )
      : cMenuEditStrItem ( Name, Value, Length, Allowed )
{
}

void cMenuEditStrItemBlind::SetValue(const char* Value)
{
  char* value=strdup ( Value );

  bool inBracket=false;
   
  for ( char* c=value; c && *c; c++ )
  {
    switch ( *c )
    {
      case '[':
        inBracket=true;
        break;
      case ']':
        inBracket=false;
        break;
      case '<':
      case '>':
        break;
      default:
        if(c==Value || (*c==' ' && *(c+1)=='\0'))
        {
          break;
        }

        if ( !inBracket )
        {
          *c='*';
        }

        break;
    }
  }

  cMenuEditStrItem::SetValue ( value );

  free ( value );
}
