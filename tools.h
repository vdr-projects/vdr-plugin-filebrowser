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

#ifndef FILEBROWSER_TOOLS_H
#define FILEBROWSER_TOOLS_H

#include <vdr/tools.h>
#include "statebag.h"

#ifdef DEBUG
  #define D(s) s
#else
  #define D(s)
#endif

template<class T> class cListContainer : public cListObject
{
  protected:
    T* Object;
    bool FreeOnDel;
  public:
    cListContainer(T *Object, bool FreeOnDel=true)
    {
      this->Object = Object;
      this->FreeOnDel = FreeOnDel;
    }
    ~cListContainer()
    {
      if(FreeOnDel && Object) delete Object;
    };
    T* GetObject() { return Object; };
    void Free() { if(Object) delete Object; };
    cListContainer<T>* Next() { return (cListContainer<T>*)cListObject::Next(); };
    cListContainer<T>* Prev() { return (cListContainer<T>*)cListObject::Prev(); };
};

class cStringContainer : public cListContainer<char>
{
  public:
    cStringContainer(char* Object, bool FreeOnDel=true) : cListContainer<char>(Object, FreeOnDel) {};
    ~cStringContainer() {};
};

class cStringContainerList : public cList<cStringContainer>
{
  public:
    bool Contains(const char* String);
    void Remove(const char* String);
};

class cConfigReader
{
  protected:
    cReadLine* Reader;
    FILE* File;
  public:
    cConfigReader(cFilebrowserStatebag* Statebag, const char* Filename);
    ~cConfigReader();
    char* Read();
  private:
    void StripComment(char* string);
    bool IsBlank(const char* string);
};

class cConfigParser
{
  protected:
    char* Line;
    char* Buffer;
    char* Pos;
    int FieldNumber;
    int CurrentLength;
    static const char Delimiter=':';
    static const char Escape='%';
  public:
    cConfigParser(char* Line, bool TakePointer=false);
    ~cConfigParser();
    char* First();
    char* Next();
    int GetFieldNumber() { return FieldNumber; };
    int GetCurrentLength() { return CurrentLength; };
};

class cCommandParser
{
  public:
    class cHandlerParameters
    {
      public:
        bool DoReplacements;
        bool ShellEscape;
        char Key;
        void* Data;
    };
    typedef char* (*ParseProc)(const char*, const char*, const cHandlerParameters*);
  protected:
    class cHandler : public cListObject
    {
      public:
        ParseProc Proc;
        cHandlerParameters Params;
    };
    class cHandlerList : public cList<cHandler> {};
    cHandlerList* Handlers;
    bool DoReplacements;
    bool ShellEscape;
    cString Command;
    static char* ReplacementHandler(const char* OrgString, const char* CurrentPos, const cHandlerParameters* Params);
  public:
    cCommandParser(const cString &Command, bool DoReplacements=true, bool ShellEscape=true);
    ~cCommandParser();
    void AddHandler(char Key, ParseProc Proc, void* Data);
    void AddReplacement(char Key, const char* String);
    cString Parse();
    /*
    Escapes a string to be used as argument for sh
    Puts it into single quotes and escapes/quotes single quotes in Argument
    Writes length of result (without \0) into EscapedLength
    You need to free the return value!
    */
    static char* EscapeShellArgument(char* Argument, int* EscapedLength);
};

#endif
