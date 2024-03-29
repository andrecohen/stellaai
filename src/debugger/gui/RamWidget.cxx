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
// $Id: RamWidget.cxx,v 1.12 2007/08/17 16:12:50 stephena Exp $
//
//   Based on code from ScummVM - Scumm Interpreter
//   Copyright (C) 2002-2004 The ScummVM project
//============================================================================

#include <sstream>

#include "OSystem.hxx"
#include "FrameBuffer.hxx"
#include "GuiUtils.hxx"
#include "GuiObject.hxx"
#include "InputTextDialog.hxx"
#include "Widget.hxx"
#include "EditTextWidget.hxx"
#include "DataGridWidget.hxx"
#include "RamDebug.hxx"
#include "RamWidget.hxx"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
RamWidget::RamWidget(GuiObject* boss, const GUI::Font& font, int x, int y)
  : Widget(boss, font, x, y, 16, 16),
    CommandSender(boss),
    myUndoAddress(-1),
    myUndoValue(-1)
{
  _type = kRamWidget;

  const int fontWidth  = font.getMaxCharWidth(),
            fontHeight = font.getFontHeight(),
            lineHeight = font.getLineHeight(),
            bwidth  = 44,//font.getStringWidth("Undo  "),
            bheight = lineHeight + 2;
  int xpos, ypos, lwidth;

  // Create a 16x8 grid holding byte values (16 x 8 = 128 RAM bytes) with labels
  xpos = x;  ypos = y + lineHeight;  lwidth = 4 * fontWidth;
  myRamGrid = new DataGridWidget(boss, font, xpos + lwidth, ypos,
                                 16, 8, 2, 8, kBASE_16);
  myRamGrid->setTarget(this);
  addFocusWidget(myRamGrid);

  // Create actions buttons to the left of the RAM grid
  xpos += lwidth + myRamGrid->getWidth() + 4;
  myUndoButton = new ButtonWidget(boss, font, xpos, ypos, bwidth, bheight,
                                  "Undo", kUndoCmd);
  myUndoButton->setTarget(this);

  ypos += bheight + 4;
  myRevertButton = new ButtonWidget(boss, font, xpos, ypos, bwidth, bheight,
                                    "Rev", kRevertCmd);
  myRevertButton->setTarget(this);

  ypos += 2 * bheight + 2;
  mySearchButton = new ButtonWidget(boss, font, xpos, ypos, bwidth, bheight,
                                    "Srch", kSearchCmd);
  mySearchButton->setTarget(this);

  ypos += bheight + 4;
  myCompareButton = new ButtonWidget(boss, font, xpos, ypos, bwidth, bheight,
                                     "Cmp", kCmpCmd);
  myCompareButton->setTarget(this);

  ypos += bheight + 4;
  myRestartButton = new ButtonWidget(boss, font, xpos, ypos, bwidth, bheight,
                                     "Rset", kRestartCmd);
  myRestartButton->setTarget(this);

  // Labels for RAM grid
  xpos = x;  ypos = y + lineHeight;
  for(int row = 0; row < 8; ++row)
  {
    new StaticTextWidget(boss, font, xpos-2, ypos + row*lineHeight + 2,
                         lwidth-2, fontHeight,
                         Debugger::to_hex_8(row*16 + kRamStart) + string(":"),
                         kTextAlignLeft);
  }
  for(int col = 0; col < 16; ++col)
  {
    new StaticTextWidget(boss, font, xpos + col*myRamGrid->colWidth() + lwidth + 8,
                         ypos - lineHeight,
                         fontWidth, fontHeight,
                         Debugger::to_hex_4(col),
                         kTextAlignLeft);
  }
  
  xpos = x + 10;  ypos += 9 * lineHeight;
  new StaticTextWidget(boss, font, xpos, ypos,
                       6*fontWidth, fontHeight,
                       "Label:", kTextAlignLeft);
  xpos += 6*fontWidth + 5;
  myLabel = new EditTextWidget(boss, font, xpos, ypos-2, 17*fontWidth,
                               lineHeight, "");
  myLabel->setEditable(false);

  xpos += 17*fontWidth + 20;
  new StaticTextWidget(boss, font, xpos, ypos, 4*fontWidth, fontHeight,
                       "Dec:", kTextAlignLeft);
  xpos += 4*fontWidth + 5;
  myDecValue = new EditTextWidget(boss, font, xpos, ypos-2, 4*fontWidth,
                                  lineHeight, "");
  myDecValue->setEditable(false);

  xpos += 4*fontWidth + 20;
  new StaticTextWidget(boss, font, xpos, ypos, 4*fontWidth, fontHeight,
                       "Bin:", kTextAlignLeft);
  xpos += 4*fontWidth + 5;
  myBinValue = new EditTextWidget(boss, font, xpos, ypos-2, 9*fontWidth,
                                  lineHeight, "");
  myBinValue->setEditable(false);

  // Calculate real dimensions
  _w = lwidth + myRamGrid->getWidth();
  _h = ypos + lineHeight - y;

  // Inputbox which will pop up when searching RAM
  StringList label;
  label.push_back("Search: ");
  myInputBox = new InputTextDialog(boss, font, label,
                                   x + lwidth + 20, y + 2*lineHeight - 5);
  myInputBox->setTarget(this);
  myInputBox->setCenter(false);

  // Start with these buttons disabled
  myCompareButton->clearFlags(WIDGET_ENABLED);
  myRestartButton->clearFlags(WIDGET_ENABLED);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
RamWidget::~RamWidget()
{
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void RamWidget::handleCommand(CommandSender* sender, int cmd, int data, int id)
{
  // We simply change the values in the ByteGridWidget
  // It will then send the 'kDGItemDataChangedCmd' signal to change the actual
  // memory location
  int addr, value;
  const char* buf;

  RamDebug& dbg = instance()->debugger().ramDebug();
  switch(cmd)
  {
    case kDGItemDataChangedCmd:
      addr  = myRamGrid->getSelectedAddr();
      value = myRamGrid->getSelectedValue();

      myUndoAddress = addr;
      myUndoValue = dbg.read(addr);

      dbg.write(addr, value);
      myDecValue->setEditString(instance()->debugger().valueToString(value, kBASE_10));
      myBinValue->setEditString(instance()->debugger().valueToString(value, kBASE_2));
      myRevertButton->setEnabled(true);
      myUndoButton->setEnabled(true);
      break;

    case kDGSelectionChangedCmd:
      addr  = myRamGrid->getSelectedAddr();
      value = myRamGrid->getSelectedValue();

      buf = instance()->debugger().equates()->getLabel(
				addr+kRamStart, EQF_RAM).c_str();
      if(*buf) myLabel->setEditString(buf);
      else    myLabel->setEditString("");

      myDecValue->setEditString(instance()->debugger().valueToString(value, kBASE_10));
      myBinValue->setEditString(instance()->debugger().valueToString(value, kBASE_2));
      break;

    case kRevertCmd:
      for(unsigned int i = 0; i < kRamSize; i++)
        dbg.write(i, myOldValueList[i]);
      fillGrid(true);
      break;

    case kUndoCmd:
      dbg.write(myUndoAddress, myUndoValue);
      myUndoButton->setEnabled(false);
      fillGrid(false);
      break;

    case kSearchCmd:
      parent()->addDialog(myInputBox);
      myInputBox->setEditString("");
      myInputBox->setTitle("");
      myInputBox->setEmitSignal(kSValEntered);
      break;

    case kCmpCmd:
      parent()->addDialog(myInputBox);
      myInputBox->setEditString("");
      myInputBox->setTitle("");
      myInputBox->setEmitSignal(kCValEntered);
      break;

    case kRestartCmd:
      doRestart();
      break;

    case kSValEntered:
    {
      const string& result = doSearch(myInputBox->getResult());
      if(result != "")
        myInputBox->setTitle(result);
      else
        parent()->removeDialog();
      break;
    }

    case kCValEntered:
    {
      const string& result = doCompare(myInputBox->getResult());
      if(result != "")
        myInputBox->setTitle(result);
      else
        parent()->removeDialog();
      break;
    }
  }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void RamWidget::loadConfig()
{
//cerr << "RamWidget::loadConfig()\n";
  fillGrid(true);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void RamWidget::fillGrid(bool updateOld)
{
  IntArray alist;
  IntArray vlist;
  BoolArray changed;

  if(updateOld) myOldValueList.clear();

  RamDebug& dbg = instance()->debugger().ramDebug();

  RamState state    = (RamState&) dbg.getState();
  RamState oldstate = (RamState&) dbg.getOldState();

  vlist = state.ram;
  if(updateOld) myOldValueList = state.ram;

  for(unsigned int i = 0; i < 16*8; i++)
  {
    alist.push_back(i);
    changed.push_back(state.ram[i] != oldstate.ram[i]);
  }

  myRamGrid->setList(alist, vlist, changed);
  if(updateOld)
  {
    myRevertButton->setEnabled(false);
    myUndoButton->setEnabled(false);
  }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
const string RamWidget::doSearch(const string& str)
{
  bool comparisonSearch = true;

  if(str.length() == 0)
  {
    // An empty field means return all memory locations
    comparisonSearch = false;
  }
  else if(str.find_first_of("+-", 0) != string::npos)
  {
    // Don't accept these characters here, only in compare
    return "Invalid input +|-";
  }

  int searchVal = instance()->debugger().stringToValue(str);

  // Clear the search array of previous items
  mySearchAddr.clear();
  mySearchValue.clear();

  // Now, search all memory locations for this value, and add it to the
  // search array
  RamDebug& dbg = instance()->debugger().ramDebug();
  for(int addr = 0; addr < kRamSize; ++addr)
  {
    int value = dbg.read(addr);

    if(comparisonSearch && searchVal != value)
      continue;

    mySearchAddr.push_back(addr);
    mySearchValue.push_back(value);
  }

  // If we have some hits, enable the comparison methods
  if(mySearchAddr.size() > 0)
  {
    mySearchButton->setEnabled(false);
    myCompareButton->setEnabled(true);
    myRestartButton->setEnabled(true);
  }

  // Finally, show the search results in the list
  myRamGrid->setHiliteList(mySearchAddr);

  return "";
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
const string RamWidget::doCompare(const string& str)
{
  bool comparitiveSearch = false;
  int searchVal = 0, offset = 0;

  if(str.length() == 0)
    return "Enter an absolute or comparitive value";

  // Do some pre-processing on the string
  string::size_type pos = str.find_first_of("+-", 0);
  if(pos > 0 && pos != string::npos)
  {
    // Only accept '+' or '-' at the start of the string
    return "Input must be [+|-]NUM";
  }

  // A comparitive search searches memory for locations that have changed by
  // the specified amount, vs. for exact values
  if(str[0] == '+' || str[0] == '-')
  {
    comparitiveSearch = true;
    bool negative = false;
    if(str[0] == '-')
      negative = true;

    string tmp = str;
    tmp.erase(0, 1);  // remove the operator
    offset = instance()->debugger().stringToValue(tmp);
    if(negative)
      offset = -offset;
  }
  else
    searchVal = instance()->debugger().stringToValue(str);

  // Now, search all memory locations specified in mySearchArray for this value
  RamDebug& dbg = instance()->debugger().ramDebug();
  IntArray tempAddrList, tempValueList;
  for(unsigned int i = 0; i < mySearchAddr.size(); ++i)
  {
    if(comparitiveSearch)
    {
      searchVal = mySearchValue[i] + offset;
      if(searchVal < 0 || searchVal > 255)
        continue;
    }

    int addr = mySearchAddr[i];
    if(dbg.read(addr) == searchVal)
    {
      tempAddrList.push_back(addr);
      tempValueList.push_back(searchVal);
    }
  }

  // Update the searchArray for the new addresses and data
  mySearchAddr = tempAddrList;
  mySearchValue = tempValueList;

  // If we have some hits, enable the comparison methods
  if(mySearchAddr.size() > 0)
  {
    myCompareButton->setEnabled(true);
    myRestartButton->setEnabled(true);
  }

  // Finally, show the search results in the list
  myRamGrid->setHiliteList(mySearchAddr);

  return "";
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void RamWidget::doRestart()
{
  // Erase all search buffers, reset to start mode
  mySearchAddr.clear();
  mySearchValue.clear();
  myRamGrid->setHiliteList(mySearchAddr);

  mySearchButton->setEnabled(true);
  myCompareButton->setEnabled(false);
  myRestartButton->setEnabled(false);
}
