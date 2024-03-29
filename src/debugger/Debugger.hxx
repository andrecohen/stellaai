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
// $Id: Debugger.hxx,v 1.90 2007/08/15 17:43:51 stephena Exp $
//============================================================================

#ifndef DEBUGGER_HXX
#define DEBUGGER_HXX

class OSystem;
class Console;
class System;
class CpuDebug;
class RamDebug;
class TIADebug;
class TiaInfoWidget;
class TiaOutputWidget;
class TiaZoomWidget;
class EditTextWidget;
class RomWidget;
class Expression;
class AIBase;

#include <map>

#include "AIBase.h"
#include "Array.hxx"
#include "DialogContainer.hxx"
#include "M6502.hxx"
#include "DebuggerParser.hxx"
#include "EquateList.hxx"
#include "PackedBitArray.hxx"
#include "PromptWidget.hxx"
#include "Rect.hxx"
#include "bspf.hxx"

typedef map<string,Expression*> FunctionMap;
typedef map<string,string> FunctionDefMap;

// Constants for RAM area
enum {
  kRamStart = 0x80,
  kRamSize = 128
};

/*
// These will probably turn out to be unneeded, left for reference for now
// pointer types for Debugger instance methods
typedef uInt8 (Debugger::*DEBUGGER_BYTE_METHOD)();
typedef uInt16 (Debugger::*DEBUGGER_WORD_METHOD)();

// call the pointed-to method on the (static) debugger object.
#define CALL_DEBUGGER_METHOD(method) ( ( Debugger::debugger().*method)() )
*/


/**
  The base dialog for all debugging widgets in Stella.  Also acts as the parent
  for all debugging operations in Stella (parser, 6502 debugger, etc).

  @author  Stephen Anthony
  @version $Id: Debugger.hxx,v 1.90 2007/08/15 17:43:51 stephena Exp $
*/
class Debugger : public DialogContainer
{
  friend class DebuggerDialog;
  friend class DebuggerParser;
  friend class EventHandler;
  friend class AIBase;

  public:
    /**
      Create a new debugger parent object
    */
    Debugger(OSystem* osystem);

    /**
      Destructor
    */
    virtual ~Debugger();

  public:
	 OSystem *getOSystem() { return myOSystem; }

    /**
      Updates the basedialog to be of the type defined for this derived class.
    */
    void initialize();

    /**
      Initialize the video subsystem wrt this class.
    */
    void initializeVideo();

    /**
      Inform this object of a console change.
    */
    void setConsole(Console* console);

    /**
      Wrapper method for EventHandler::enterDebugMode() for those classes
      that don't have access to EventHandler.

      @param message  Message to display when entering debugger
      @param data     An address associated with the message
    */
    bool start(const string& message = "", int address = -1);

    /**
      Wrapper method for EventHandler::leaveDebugMode() for those classes
      that don't have access to EventHandler.
    */
    void quit();

	 void addFunction(string name, string def, Expression *exp, bool builtin=false);
	 string getFunctionDef(string name);
	 void delFunction(string name);
	 Expression *getFunction(string name);
	 const FunctionDefMap getFunctionDefMap();
	 const string builtinHelp();

    /**
      The debugger subsystem responsible for all CPU state
    */
    CpuDebug& cpuDebug() const { return *myCpuDebug; }

    /**
      The debugger subsystem responsible for all RAM state
    */
    RamDebug& ramDebug() const { return *myRamDebug; }

    /**
      The debugger subsystem responsible for all TIA state
    */
    TIADebug& tiaDebug() const { return *myTiaDebug; }

    /**
      List of English-like aliases for 6502 opcodes and operands.
    */
    EquateList *equates();

    DebuggerParser *parser() { return myParser; }

    PackedBitArray *breakpoints() { return breakPoints; }
    PackedBitArray *readtraps() { return readTraps; }
    PackedBitArray *writetraps() { return writeTraps; }

    /**
      Run the debugger command and return the result.
    */
    const string run(const string& command);

    /**
      Give the contents of the CPU registers and disassembly of
      next instruction.
    */
    const string cpuState();

    /**
      Get contents of RIOT switch & timer registers
    */
    const string riotState();

    /**
      The current cycle count of the System.
    */
    int cycles();

    /**
      Disassemble from the starting address the specified number of lines
      and place result in a string.
    */
    const string& disassemble(int start, int lines);

    /**
      Disassemble from the starting address the specified number of lines
      and place addresses, bytes and data in given arrays.
    */
    void disassemble(IntArray& addr, StringList& addrLabel,
                     StringList& bytes, StringList& data,
                     int start, int lines);

    void autoExec();

    string showWatches();

    /**
      Convert between string->integer and integer->string, taking into
      account the current base format.
    */
    int stringToValue(const string& stringval)
        { return myParser->decipher_arg(stringval); }
    const string valueToString(int value, BaseFormat outputBase = kBASE_DEFAULT);

    /** Convenience methods to convert to/from base values */
    static char* to_hex_4(int i)
    {
      static char out[2];
      sprintf(out, "%1x", i);
      return out;
    }
    static char* to_hex_8(int i)
    {
      static char out[3];
      sprintf(out, "%02x", i);
      return out;
    }
    static char* to_hex_16(int i)
    {
      static char out[5];
      sprintf(out, "%04x", i);
      return out;
    }
    static char* to_bin(int dec, int places, char *buf) {
      int bit = 1;
      buf[places] = '\0';
      while(--places >= 0) {
        if(dec & bit) buf[places] = '1';
        else          buf[places] = '0';
        bit <<= 1;
      }
      return buf;
    }
    static char* to_bin_8(int dec) {
      static char buf[9];
      return to_bin(dec, 8, buf);
    }
    static char* to_bin_16(int dec) {
      static char buf[17];
      return to_bin(dec, 16, buf);
    }
    static int conv_hex_digit(char d) {
      if(d >= '0' && d <= '9')      return d - '0';
      else if(d >= 'a' && d <= 'f') return d - 'a' + 10;
      else if(d >= 'A' && d <= 'F') return d - 'A' + 10;
      else                          return -1;
    }

    /**
      This is used when we want the debugger from a class that can't
      receive the debugger object in any other way.

      It's basically a hack to prevent the need to pass debugger objects
      everywhere, but I feel it's better to place it here then in
      YaccParser (which technically isn't related to it at all).
    */
    static Debugger& debugger() { return *myStaticDebugger; }

    /**
      Get the dimensions of the various debugger dialog areas
      (takes mediasource into account)
    */
    GUI::Rect getDialogBounds() const;
    GUI::Rect getTiaBounds() const;
    GUI::Rect getRomBounds() const;
    GUI::Rect getStatusBounds() const;
    GUI::Rect getTabBounds() const;

    /* These are now exposed so Expressions can use them. */
    int peek(int addr);
    int dpeek(int addr);
    int getBank();
    int bankCount();

    void setBreakPoint(int bp, bool set);

    string loadListFile(string f = "");
    const string getSourceLines(int addr);
    bool haveListFile() { return sourceLines.size() > 0; }

    bool saveROM(string filename);

    bool setBank(int bank);
    bool patchROM(int addr, int value);

    void lockState();
    void unlockState();
	
	/**
	 Return a formatted string containing the contents of the specified
	 device.
	 */
    const string dumpRAM();
    const string dumpTIA();

  private:
    /**
      Save state of each debugger subsystem
    */
    void saveOldState();

    /**
      Set initial state before entering the debugger.
    */
    void setStartState();

    /**
      Set final state before leaving the debugger.
    */
    void setQuitState();

    int step();
    int trace();
    void nextScanline(int lines);
    void nextFrame(int frames);

    void toggleBreakPoint(int bp);

    bool breakPoint(int bp);
    void toggleReadTrap(int t);
    void toggleWriteTrap(int t);
    void toggleTrap(int t);
    bool readTrap(int t);
    bool writeTrap(int t);
    void clearAllTraps();

    void reloadROM();

    // set a bunch of RAM locations at once
    const string setRAM(IntArray& args);

    void reset();
    void autoLoadSymbols(string file);
    void clearAllBreakPoints();

    void formatFlags(BoolArray& b, char *out);
    PromptWidget *prompt() { return myPrompt; }
    void addLabel(string label, int address);

    const char *getCartType();
    void saveState(int state);
    void loadState(int state);

    const string invIfChanged(int reg, int oldReg);

  private:
    typedef multimap<string,string> ListFile;
    typedef ListFile::const_iterator ListIter;

    Console* myConsole;
    System* mySystem;

    DebuggerParser* myParser;
    CpuDebug* myCpuDebug;
    RamDebug* myRamDebug;
    TIADebug* myTiaDebug;

    TiaInfoWidget*   myTiaInfo;
    TiaOutputWidget* myTiaOutput;
    TiaZoomWidget*   myTiaZoom;
    RomWidget*       myRom;
    EditTextWidget*  myMessage;

    EquateList *equateList;
    PackedBitArray *breakPoints;
    PackedBitArray *readTraps;
    PackedBitArray *writeTraps;
    PromptWidget *myPrompt;

    ListFile sourceLines;

    static Debugger* myStaticDebugger;

    FunctionMap functions;
    FunctionDefMap functionDefs;

    // Dimensions of the entire debugger window
    uInt32 myWidth;
    uInt32 myHeight;
};

#endif
