//============================================================================
//
//   SSSS    tt          lll  lll       
//  SS  SS   tt           ll   ll        
//  SS     tttttt  eeee   ll   ll   aaaa 
//   SSSS    tt   ee  ee  ll   ll      aa
//      SS   tt   eeeeee  ll   ll   aaaaa  --  "An Atari 2600 VCS Emulator"
//  SS  SS   tt   ee      ll   ll  aa  aa
//   SSSS     ttt  eeeee llll llll  aaaaa
//
// Copyright (c) 1995-2007 by Bradford W. Mott and the Stella team
//
// See the file "license" for information on usage and redistribution of
// this file, and for a DISCLAIMER OF ALL WARRANTIES.
//
// $Id: InputTextDialog.hxx,v 1.9 2007/01/01 18:04:53 stephena Exp $
//
//   Based on code from ScummVM - Scumm Interpreter
//   Copyright (C) 2002-2004 The ScummVM project
//============================================================================

#ifndef INPUT_TEXT_DIALOG_HXX
#define INPUT_TEXT_DIALOG_HXX

class GuiObject;
class StaticTextWidget;
class EditTextWidget;

#include "Dialog.hxx"
#include "Command.hxx"

typedef Common::Array<EditTextWidget*> InputWidget;

class InputTextDialog : public Dialog, public CommandSender
{
  public:
    InputTextDialog(GuiObject* boss, const GUI::Font& font,
                    const StringList& labels, int x, int y);
    virtual ~InputTextDialog();

    const string& getResult(int idx = 0);

    void setEditString(const string& str, int idx = 0);
    void setEmitSignal(int cmd) { myCmd = cmd; }
    void setTitle(const string& title);

    void setFocus(int idx = 0);

  protected:
    virtual void handleCommand(CommandSender* sender, int cmd, int data, int id);

  private:
  private:
    InputWidget       myInput;
    StaticTextWidget* myTitle;

    bool myErrorFlag;
    int	 myCmd;

    enum {
      kAcceptCmd = 'ACPT'
    };
};

#endif
