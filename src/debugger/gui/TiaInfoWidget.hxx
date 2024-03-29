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
// $Id: TiaInfoWidget.hxx,v 1.5 2007/01/01 18:04:44 stephena Exp $
//
//   Based on code from ScummVM - Scumm Interpreter
//   Copyright (C) 2002-2004 The ScummVM project
//============================================================================

#ifndef TIA_INFO_WIDGET_HXX
#define TIA_INFO_WIDGET_HXX

class GuiObject;
class EditTextWidget;

#include "Widget.hxx"
#include "Command.hxx"


class TiaInfoWidget : public Widget, public CommandSender
{
  public:
    TiaInfoWidget(GuiObject *boss, const GUI::Font& font, int x, int y);
    virtual ~TiaInfoWidget();

    void loadConfig();

  protected:
    void handleMouseDown(int x, int y, int button, int clickCount);
    void handleCommand(CommandSender* sender, int cmd, int data, int id);

  private:
    EditTextWidget* myFrameCount;
    EditTextWidget* myFrameCycles;

    EditTextWidget* myScanlineCount;
    EditTextWidget* myScanlineCycles;
    EditTextWidget* myPixelPosition;
    EditTextWidget* myColorClocks;

    CheckboxWidget* myVSync;
    CheckboxWidget* myVBlank;
};

#endif
