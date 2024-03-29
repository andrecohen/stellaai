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
// $Id: AboutDialog.cxx,v 1.21 2007/08/15 17:43:51 stephena Exp $
//
//   Based on code from ScummVM - Scumm Interpreter
//   Copyright (C) 2002-2004 The ScummVM project
//============================================================================

#include "OSystem.hxx"
#include "Widget.hxx"
#include "Dialog.hxx"
#include "GuiUtils.hxx"
#include "Version.hxx"
#include "AboutDialog.hxx"

#define ADD_ATEXT(d) do { dsc[i] = d; i++; } while(0)
#define ADD_ALINE ADD_ATEXT("")

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
AboutDialog::AboutDialog(OSystem* osystem, DialogContainer* parent,
                         const GUI::Font& font, int x, int y, int w, int h)
    : Dialog(osystem, parent, x, y, w, h),
      myPage(1),
      myNumPages(6)
{
  WidgetArray wid;

  // Add Previous, Next and Close buttons
  myPrevButton = addButton(font, 10, h - 24, "Previous", kPrevCmd);
  myPrevButton->clearFlags(WIDGET_ENABLED);
  wid.push_back(myPrevButton);

  myNextButton = addButton(font, (kButtonWidth + 15), h - 24,
                           "Next", kNextCmd);
  wid.push_back(myNextButton);

  ButtonWidget* b = addButton(font, w - (kButtonWidth + 10), h - 24,
                              "Close", kCloseCmd);
  wid.push_back(b);
  addOKWidget(b);  addCancelWidget(b);

  myTitle = new StaticTextWidget(this, font, 5, 5, w - 10, font.getFontHeight(),
                                 "", kTextAlignCenter);
  myTitle->setTextColor(kTextColorEm);

  for(int i = 0; i < LINES_PER_PAGE; i++)
  {
    myDesc[i] = new StaticTextWidget(this, font, 10, 18 + (10 * i), w - 20,
                                     font.getFontHeight(), "", kTextAlignLeft);
  }

  addToFocusList(wid);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
AboutDialog::~AboutDialog()
{
}

// The following commands can be put at the start of a line (all subject to change):
//   \C, \L, \R  -- set center/left/right alignment
//   \c0 - \c5   -- set a custom color:
//                  0 normal text (green)
//                  1 highlighted text (light green)
//                  2 light border (light gray)
//                  3 dark border (dark gray)
//                  4 background (black)
//                  5 emphasized text (red)
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void AboutDialog::updateStrings(int page, int lines, string& title, string* &dsc)
{
  dsc = new string[lines];

  int i = 0;
  switch(page)
  {
    case 1:
      title = string("Stella ") + STELLA_VERSION;
      ADD_ATEXT("\\CA multi-platform Atari 2600 VCS emulator");
      ADD_ATEXT(string("\\C\\c2") + instance()->features());
      ADD_ALINE;
      ADD_ATEXT("\\CCopyright (C) 1995-2007 The Stella team");
      ADD_ATEXT("\\Chttp://stella.sourceforge.net");
      ADD_ALINE;
      ADD_ATEXT("Stella is free software released under the GNU GPL");
      ADD_ATEXT("See manual for further details");
      break;

    case 2:
      title = "The Stella team";
      ADD_ATEXT("\\L\\c0""  Bradford W. Mott");
      ADD_ATEXT("\\L\\c2""    Original author, lead developer");
      ADD_ATEXT("\\L\\c0""  Stephen Anthony");
      ADD_ATEXT("\\L\\c2""    Lead developer, Linux/Win32 maintainer");
      ADD_ATEXT("\\L\\c0""  Mark Grebe");
      ADD_ATEXT("\\L\\c2""    Author/maintainer for OSX port");
      ADD_ATEXT("\\L\\c0""  Brian Watson");
      ADD_ATEXT("\\L\\c2""    Emulation core enhancement, debugger support");
      ADD_ATEXT("\\L\\c0""  Eckhard Stolberg");
      ADD_ATEXT("\\L\\c2""    Emulation core development");
      break;

    case 3:
      title = "The Stella team";
      ADD_ATEXT("\\L\\c0""  Joe D'Andrea");
      ADD_ATEXT("\\L\\c2""    Maintainer for Solaris port");
      ADD_ATEXT("\\L\\c0""  Darrell Spice Jr. & Doodle");
      ADD_ATEXT("\\L\\c2""    Authors for OS/2 port");
      ADD_ATEXT("\\L\\c0""  Kostas Nakos");
      ADD_ATEXT("\\L\\c2""    Author/maintainer for WinCE port");
      ADD_ATEXT("\\L\\c0""  Alex Zaballa");
      ADD_ATEXT("\\L\\c2""    Maintainer for GP2X port");
      break;

    case 4:
      title = "Retired members / Contributors";
      ADD_ATEXT("\\L\\c0""See Stella manual for contribution details");
      ADD_ALINE;
      ADD_ATEXT("\\L\\c0""  David Aspell, Chris Bennett, Alexander Bilstein");
      ADD_ATEXT("\\L\\c0""  Dan Boris, Piero Cavina, Bob Colbert");
      ADD_ATEXT("\\L\\c0""  Renato Ferreira, Ron Fries, Aaron Giles");
      ADD_ATEXT("\\L\\c0""  Mark Hahn, Kevin Horton, Thomas Jentzsch");
      ADD_ATEXT("\\L\\c0""  Erik \"Voch\" Kovach, Daniel Marks, James Mcclain");
      ADD_ATEXT("\\L\\c0""  David McEwen, Jeff Miller, Dan Mowczan");
      ADD_ATEXT("\\L\\c0""  Jack Nutting, Manuel Polik, Jim Pragit");
      ADD_ATEXT("\\L\\c0""  John Saeger, Chris Salomon, Jason Scott");
      break;

    case 5:
      title = "Retired members / Contributors";
      ADD_ATEXT("\\L\\c0""See Stella manual for contribution details");
      ADD_ALINE;
      ADD_ATEXT("\\L\\c0""  David Shaw, Raul Silva, Chris Snell, John Stiles");
      ADD_ATEXT("\\L\\c0""  Matthew Stroup, Joel Sutton, Greg Troutman");
      ADD_ATEXT("\\L\\c0""  Curt Vendel, Keith Wilkins, Jeff Wisnia");
      ADD_ALINE;
      ADD_ATEXT("\\L\\c0""And many others ...");
      ADD_ALINE;
      ADD_ATEXT("\\L\\c0""Thanks to the ScummVM project for the GUI code");
      break;

    case 6:
      title = "Cast of thousands";
      ADD_ATEXT("\\L\\c0""Special thanks to AtariAge for introducing the");
      ADD_ATEXT("\\L\\c0""Atari 2600 to a whole new generation");
      ADD_ATEXT("\\L\\c2""  http://www.atariage.com");
      ADD_ALINE;
      ADD_ATEXT("\\L\\c0""Finally, a huge thanks to the original Atari 2600");
      ADD_ATEXT("\\L\\c0""VCS team for giving us the magic, and to the");
      ADD_ATEXT("\\L\\c0""homebrew developers for keeping the magic alive");
      break;
  }

  while(i < lines)
    ADD_ALINE;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void AboutDialog::displayInfo()
{
  string titleStr, *dscStr;

  updateStrings(myPage, LINES_PER_PAGE, titleStr, dscStr);

  myTitle->setLabel(titleStr);
  for(int i = 0; i < LINES_PER_PAGE; i++)
  {
    const char *str = dscStr[i].c_str();
    TextAlignment align = kTextAlignCenter;
    int color  = kTextColor;

    while (str[0] == '\\')
    {
      switch (str[1])
      {
        case 'C':
          align = kTextAlignCenter;
          break;

        case 'L':
          align = kTextAlignLeft;
          break;

        case 'R':
          align = kTextAlignRight;
          break;

        case 'c':
          switch (str[2])
          {
            case '0':
              color = kTextColor;
              break;
            case '1':
              color = kTextColorHi;
              break;
            case '2':
              color = kColor;
              break;
            case '3':
              color = kShadowColor;
              break;
            case '4':
              color = kBGColor;
              break;
            case '5':
              color = kTextColorEm;
              break;
            default:
              break;
          }
          str++;
          break;

        default:
          break;
      }
      str += 2;
    }

    myDesc[i]->setAlign(align);
    myDesc[i]->setTextColor(color);
    myDesc[i]->setLabel(str);
  }

  delete[] dscStr;

  // Redraw entire dialog
  _dirty = true;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void AboutDialog::handleCommand(CommandSender* sender, int cmd, int data, int id)
{
  switch(cmd)
  {
    case kNextCmd:
      myPage++;
      if(myPage >= myNumPages)
        myNextButton->clearFlags(WIDGET_ENABLED);
      if(myPage >= 2)
        myPrevButton->setFlags(WIDGET_ENABLED);

      displayInfo();
      break;

    case kPrevCmd:
      myPage--;
      if(myPage <= myNumPages)
        myNextButton->setFlags(WIDGET_ENABLED);
      if(myPage <= 1)
        myPrevButton->clearFlags(WIDGET_ENABLED);

      displayInfo();
      break;

    default:
      Dialog::handleCommand(sender, cmd, data, 0);
  }
}
