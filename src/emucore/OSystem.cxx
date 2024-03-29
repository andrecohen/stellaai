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
// $Id: OSystem.cxx,v 1.108 2007/08/17 16:12:50 stephena Exp $
//============================================================================

#include <cassert>
#include <sstream>
#include <fstream>
#include <iostream>
#include <zlib.h>

#include "MediaFactory.hxx"

#ifdef DEBUGGER_SUPPORT
  #include "Debugger.hxx"
#endif

#ifdef CHEATCODE_SUPPORT
  #include "CheatManager.hxx"
#endif

#include "FSNode.hxx"
#include "unzip.h"
#include "MD5.hxx"
#include "Settings.hxx"
#include "PropsSet.hxx"
#include "EventHandler.hxx"
#include "Menu.hxx"
#include "CommandMenu.hxx"
#include "Launcher.hxx"
#include "Font.hxx"
#include "StellaFont.hxx"
#include "ConsoleFont.hxx"
#include "bspf.hxx"
#include "OSystem.hxx"
#include "Widget.hxx"

#include "AISettings.h"

#define BASE_DEFAULT	0
#define BASE_STATS		1

#define MAX_ROM_SIZE  512 * 1024

#include <time.h>
#include <sys/time.h>


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
OSystem::OSystem()
  : myEventHandler(NULL),
	myFrameBuffer(NULL),
	mySound(NULL),
	mySettings(NULL),
	myPropSet(NULL),
	myConsole(NULL),
	myMenu(NULL),
	myCommandMenu(NULL),
	myLauncher(NULL),
	myDebugger(NULL),
	myCheatManager(NULL),
	myQuitLoop(false),
	myRomFile(""),
	myFeatures(""),
	myFont(NULL),
	myConsoleFont(NULL)
{
#ifdef DISPLAY_OPENGL
  myFeatures += "OpenGL ";
#endif
#ifdef SOUND_SUPPORT
  myFeatures += "Sound ";
#endif
#ifdef JOYSTICK_SUPPORT
  myFeatures += "Joystick ";
#endif
#ifdef DEBUGGER_SUPPORT
  myFeatures += "Debugger ";
#endif
#ifdef CHEATCODE_SUPPORT
  myFeatures += "Cheats";
#endif

#if 0
  // Debugging info for the GUI widgets
  cerr << "  kStaticTextWidget   = " << kStaticTextWidget   << endl;
  cerr << "  kEditTextWidget     = " << kEditTextWidget     << endl;
  cerr << "  kButtonWidget       = " << kButtonWidget       << endl;
  cerr << "  kCheckboxWidget     = " << kCheckboxWidget     << endl;
  cerr << "  kSliderWidget       = " << kSliderWidget       << endl;
  cerr << "  kListWidget         = " << kListWidget         << endl;
  cerr << "  kScrollBarWidget    = " << kScrollBarWidget    << endl;
  cerr << "  kPopUpWidget        = " << kPopUpWidget        << endl;
  cerr << "  kTabWidget          = " << kTabWidget	        << endl;
  cerr << "  kEventMappingWidget = " << kEventMappingWidget << endl;
  cerr << "  kEditableWidget     = " << kEditableWidget     << endl;
  cerr << "  kAudioWidget        = " << kAudioWidget        << endl;
  cerr << "  kColorWidget        = " << kColorWidget        << endl;
  cerr << "  kCpuWidget          = " << kCpuWidget          << endl;
  cerr << "  kDataGridOpsWidget  = " << kDataGridOpsWidget  << endl;
  cerr << "  kDataGridWidget     = " << kDataGridWidget     << endl;
  cerr << "  kPromptWidget       = " << kPromptWidget       << endl;
  cerr << "  kRamWidget          = " << kRamWidget          << endl;
  cerr << "  kRomListWidget      = " << kRomListWidget      << endl;
  cerr << "  kRomWidget          = " << kRomWidget          << endl;
  cerr << "  kTiaInfoWidget      = " << kTiaInfoWidget      << endl;
  cerr << "  kTiaOutputWidget    = " << kTiaOutputWidget    << endl;
  cerr << "  kTiaWidget          = " << kTiaWidget          << endl;
  cerr << "  kTiaZoomWidget      = " << kTiaZoomWidget      << endl;
  cerr << "  kToggleBitWidget    = " << kToggleBitWidget    << endl;
  cerr << "  kTogglePixelWidget  = " << kTogglePixelWidget  << endl;
  cerr << "  kToggleWidget       = " << kToggleWidget       << endl;
#endif
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
OSystem::~OSystem()
{
  delete myMenu;
  delete myCommandMenu;
  delete myLauncher;
  delete myFont;
  delete myConsoleFont;

  // Remove any game console that is currently attached
  deleteConsole();

  // OSystem takes responsibility for framebuffer and sound,
  // since it created them
  delete myFrameBuffer;
  delete mySound;

  // These must be deleted after all the others
  // This is a bit hacky, since it depends on ordering
  // of d'tor calls
#ifdef DEBUGGER_SUPPORT
  delete myDebugger;
#endif
#ifdef CHEATCODE_SUPPORT
  delete myCheatManager;
#endif

  delete myPropSet;
  delete myEventHandler;

  delete aiBase; 
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool OSystem::create()
{
  // Get updated paths for all configuration files
  setConfigPaths();

  // Get relevant information about the video hardware
  // This must be done before any graphics context is created, since
  // it may be needed to initialize the size of graphical objects
  queryVideoHardware();

  // Create fonts to draw text
  myFont         = new GUI::Font(GUI::stellaDesc);
  myLauncherFont = new GUI::Font(GUI::stellaDesc);
  myConsoleFont  = new GUI::Font(GUI::consoleDesc);

  // Create the event handler for the system
  myEventHandler = new EventHandler(this);
  myEventHandler->initialize();

  // Create a properties set for us to use and set it up
  myPropSet = new PropertiesSet(this);

#ifdef CHEATCODE_SUPPORT
  myCheatManager = new CheatManager(this);
  myCheatManager->loadCheatDatabase();
#endif

  // Create menu and launcher GUI objects
  myMenu = new Menu(this);
  myCommandMenu = new CommandMenu(this);
  myLauncher = new Launcher(this);
#ifdef DEBUGGER_SUPPORT
  myDebugger = new Debugger(this);
#endif

  // Create the sound object; the sound subsystem isn't actually
  // opened until needed, so this is non-blocking (on those systems
  // that only have a single sound device (no hardware mixing)
  createSound();
  
  aiBase = new AIBase(this);

  return true;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void OSystem::setConfigPaths()
{
  myStateDir = mySettings->getString("statedir");
  if(myStateDir == "")
	myStateDir = myBaseDir + BSPF_PATH_SEPARATOR + "state";
  if(!FilesystemNode::dirExists(myStateDir))
	FilesystemNode::makeDir(myStateDir);
  mySettings->setString("statedir", myStateDir);

  myGameListCacheFile = myBaseDir + BSPF_PATH_SEPARATOR + "stella.cache";

  myCheatFile = mySettings->getString("cheatfile");
  if(myCheatFile == "")
	myCheatFile = myBaseDir + BSPF_PATH_SEPARATOR + "stella.cht";
  mySettings->setString("cheatfile", myCheatFile);

  myPaletteFile = mySettings->getString("palettefile");
  if(myPaletteFile == "")
	myPaletteFile = myBaseDir + BSPF_PATH_SEPARATOR + "stella.pal";
  mySettings->setString("palettefile", myPaletteFile);

  myPropertiesFile = mySettings->getString("propsfile");
  if(myPropertiesFile == "")
	myPropertiesFile = myBaseDir + BSPF_PATH_SEPARATOR + "stella.pro";
  mySettings->setString("propsfile", myPropertiesFile);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void OSystem::setUIPalette()
{
  int palette = mySettings->getInt("uipalette") - 1;
  if(palette < 0 || palette >= kNumUIPalettes) palette = 0;
  myFrameBuffer->setUIPalette(&ourGUIColors[palette][0]);
  myEventHandler->refreshDisplay();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void OSystem::setBaseDir(const string& basedir)
{
  myBaseDir = basedir;
  if(!FilesystemNode::dirExists(myBaseDir))
	FilesystemNode::makeDir(myBaseDir);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void OSystem::setFramerate(uInt32 framerate)
{
  myDisplayFrameRate = framerate;
  myTimePerFrame = (uInt32)(1000000.0 / (double)myDisplayFrameRate);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool OSystem::createFrameBuffer(bool showmessage)
{
  // Check if we can re-use the current framebuffer
  bool changeBuffer = (myFrameBuffer == NULL);
  if(!changeBuffer)
  {
	if((mySettings->getString("video") == "soft" &&
		myFrameBuffer->type() != kSoftBuffer) ||
	   (mySettings->getString("video") == "gl" &&
		myFrameBuffer->type() != kGLBuffer))
	  changeBuffer = true;
  }
  // Now we only create when absolutely necessary
  if(changeBuffer)
  {
	delete myFrameBuffer;
	myFrameBuffer = MediaFactory::createVideo(this);
  }

  // Re-initialize the framebuffer to current settings
  switch(myEventHandler->state())
  {
	case EventHandler::S_EMULATE:
	case EventHandler::S_PAUSE:
	case EventHandler::S_MENU:
	case EventHandler::S_CMDMENU:
	  myConsole->initializeVideo();
	  break;  // S_EMULATE, S_PAUSE, S_MENU, S_CMDMENU

	case EventHandler::S_LAUNCHER:
	  myLauncher->initializeVideo();
	  break;  // S_LAUNCHER

#ifdef DEBUGGER_SUPPORT
	case EventHandler::S_DEBUGGER:
	  myDebugger->initializeVideo();
	  break;  // S_DEBUGGER
#endif

	default:
	  break;
  }

  // Setup the SDL joysticks (must be done after FrameBuffer is created)
  if(changeBuffer) myEventHandler->setupJoysticks();

  // Update the UI palette
  setUIPalette();

  if(showmessage)
  {
	switch(myFrameBuffer->type())
	{
	  case kSoftBuffer:
		myFrameBuffer->showMessage("Software mode");
		break;
	  case kGLBuffer:
		myFrameBuffer->showMessage("OpenGL mode");
		break;
	}
  }

  return true;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void OSystem::toggleFrameBuffer()
{
#ifdef DISPLAY_OPENGL
  // First figure out which mode to switch to
  string video = mySettings->getString("video");
  if(video == "soft")
	video = "gl";
  else if(video == "gl")
	video = "soft";
  else   // a driver that doesn't exist was requested, so use software mode
	video = "soft";

  // Update the settings and create the framebuffer
  mySettings->setString("video", video);
  createFrameBuffer(true);  // show onscreen message, re-initialize framebuffer

  // The palette and phosphor info for the framebuffer will be lost
  // when a new framebuffer is created; we must restore it
  if(myConsole)
	myConsole->initializeVideo(false);
#endif
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void OSystem::createSound()
{
  delete mySound;  mySound = NULL;
  mySound = MediaFactory::createAudio(this);
#ifndef SOUND_SUPPORT
  mySettings->setBool("sound", false);
#endif
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool OSystem::createConsole(const string& romfile)
{
  // Do a little error checking; it shouldn't be necessary
  if(myConsole) deleteConsole();

  bool retval = false, showmessage = false;

  // If a blank ROM has been given, we reload the current one (assuming one exists)
  if(romfile == "")
  {
	showmessage = true;  // we show a message if a ROM is being reloaded
	if(myRomFile == "")
	{
	  cerr << "ERROR: Rom file not specified ..." << endl;
	  return false;
	}
  }
  else
	myRomFile = romfile;

  // Open the cartridge image and read it in
  uInt8* image;
  int size = -1;
  string md5;
  if(openROM(myRomFile, md5, &image, &size))
  {
	// Get all required info for creating a valid console
	Cartridge* cart = (Cartridge*) NULL;
	Properties props;
	if(queryConsoleInfo(image, size, md5, &cart, props))
	{
	  // Create an instance of the 2600 game console
	  myConsole = new Console(this, cart, props);
	#ifdef CHEATCODE_SUPPORT
	  myCheatManager->loadCheats(md5);
	#endif
	  myEventHandler->reset(EventHandler::S_EMULATE);
	  createFrameBuffer(false);  // Takes care of initializeVideo()
	  myConsole->initializeAudio();
	#ifdef DEBUGGER_SUPPORT
	  myDebugger->setConsole(myConsole);
	  myDebugger->initialize();
	#endif

	  if(showmessage)
		myFrameBuffer->showMessage("New console created");
	  if(mySettings->getBool("showinfo"))
		cout << "Game console created:" << endl
			 << "  ROM file:  " << myRomFile << endl
			 << myConsole->about() << endl;

	  // Update the timing info for a new console run
	  resetLoopTiming();

	  myFrameBuffer->setCursorState();
	  retval = true;
	}
	else
	{
	  cerr << "ERROR: Couldn't create console for " << myRomFile << " ..." << endl;
	  retval = false;
	}
  }
  else
  {
	cerr << "ERROR: Couldn't open " << myRomFile << " ..." << endl;
	retval = false;
  }

  // Free the image since we don't need it any longer
  if(size != -1)
	delete[] image;

  return retval;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void OSystem::deleteConsole()
{
  if(myConsole)
  {
	mySound->close();
  #ifdef CHEATCODE_SUPPORT
	myCheatManager->saveCheats(myConsole->properties().get(Cartridge_MD5));
  #endif
	if(mySettings->getBool("showinfo"))
	{
	  double executionTime   = (double) myTimingInfo.totalTime / 1000000.0;
	  double framesPerSecond = (double) myTimingInfo.totalFrames / executionTime;
	  cout << "Game console stats:" << endl
		   << "  Total frames drawn: " << myTimingInfo.totalFrames << endl
		   << "  Total time (sec):   " << executionTime << endl
		   << "  Frames per second:  " << framesPerSecond << endl
		   << endl;
	}
	delete myConsole;  myConsole = NULL;
  }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void OSystem::createLauncher()
{
  myEventHandler->reset(EventHandler::S_LAUNCHER);
  createFrameBuffer(false);
  myLauncher->reStack();
  myFrameBuffer->setCursorState();
  myEventHandler->refreshDisplay();

  setFramerate(60);
  resetLoopTiming();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool OSystem::openROM(const string& rom, string& md5, uInt8** image, int* size)
{
  // Try to open the file as a zipped archive
  // If that fails, we assume it's just a gzipped or normal data file
  unzFile tz;
  if((tz = unzOpen(rom.c_str())) != NULL)
  {
	if(unzGoToFirstFile(tz) == UNZ_OK)
	{
	  unz_file_info ufo;

	  for(;;)  // Loop through all files for valid 2600 images
	  {
		// Longer filenames might be possible, but I don't
		// think people would name files that long in zip files...
		char filename[1024];

		unzGetCurrentFileInfo(tz, &ufo, filename, 1024, 0, 0, 0, 0);
		filename[1023] = '\0';

		if(strlen(filename) >= 4)
		{
		  // Grab 3-character extension
		  char* ext = filename + strlen(filename) - 4;

		  if(!BSPF_strcasecmp(ext, ".bin") || !BSPF_strcasecmp(ext, ".a26"))
			break;
		}

		// Scan the next file in the zip
		if(unzGoToNextFile(tz) != UNZ_OK)
		  break;
	  }

	  // Now see if we got a valid image
	  if(ufo.uncompressed_size <= 0)
	  {
		unzClose(tz);
		return false;
	  }
	  *size  = ufo.uncompressed_size;
	  *image = new uInt8[*size];

	  // We don't have to check for any return errors from these functions,
	  // since if there are, 'image' will not contain a valid ROM and the
	  // calling method can take of it
	  unzOpenCurrentFile(tz);
	  unzReadCurrentFile(tz, *image, *size);
	  unzCloseCurrentFile(tz);
	  unzClose(tz);
	}
	else
	{
	  unzClose(tz);
	  return false;
	}
  }
  else
  {
	// Assume the file is either gzip'ed or not compressed at all
	gzFile f = gzopen(rom.c_str(), "rb");
	if(!f)
	  return false;

	*image = new uInt8[MAX_ROM_SIZE];
	*size = gzread(f, *image, MAX_ROM_SIZE);
	gzclose(f);
  }

  // If we get to this point, we know we have a valid file to open
  // Now we make sure that the file has a valid properties entry
  md5 = MD5(*image, *size);

  // Some games may not have a name, since there may not
  // be an entry in stella.pro.  In that case, we use the rom name
  // and reinsert the properties object
  Properties props;
  myPropSet->getMD5(md5, props);

  string name = props.get(Cartridge_Name);
  if(name == "Untitled")
  {
	// Get the filename from the rom pathname
	string::size_type pos = rom.find_last_of(BSPF_PATH_SEPARATOR);
	if(pos+1 != string::npos)
	{
	  name = rom.substr(pos+1);
	  props.set(Cartridge_MD5, md5);
	  props.set(Cartridge_Name, name);
	  myPropSet->insert(props, false);
	}
  }

  return true;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
string OSystem::getROMInfo(const string& romfile)
{
  ostringstream buf;

  // Open the cartridge image and read it in
  uInt8* image;
  int size = -1;
  string md5;
  if(openROM(romfile, md5, &image, &size))
  {
	// Get all required info for creating a temporary console
	Cartridge* cart = (Cartridge*) NULL;
	Properties props;
	if(queryConsoleInfo(image, size, md5, &cart, props))
	{
	  Console* console = new Console(this, cart, props);
	  if(console)
		buf << console->about();
	  else
		buf << "ERROR: Couldn't get ROM info for " << romfile << " ..." << endl;

	  delete console;
	}
	else
	  buf << "ERROR: Couldn't open " << romfile << " ..." << endl;
  }
  // Free the image and console since we don't need it any longer
  if(size != -1)
	delete[] image;

  return buf.str();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool OSystem::queryConsoleInfo(const uInt8* image, uInt32 size,
							   const string& md5,
							   Cartridge** cart, Properties& props)
{
  // Get a valid set of properties, including any entered on the commandline
  string s;
  myPropSet->getMD5(md5, props);


  s = mySettings->getString("type");
  if(s != "") props.set(Cartridge_Type, s);
  s = mySettings->getString("channels");
  if(s != "") props.set(Cartridge_Sound, s);
  s = mySettings->getString("ld");
  if(s != "") props.set(Console_LeftDifficulty, s);
  s = mySettings->getString("rd");
  if(s != "") props.set(Console_RightDifficulty, s);
  s = mySettings->getString("tv");
  if(s != "") props.set(Console_TelevisionType, s);
  s = mySettings->getString("sp");
  if(s != "") props.set(Console_SwapPorts, s);
  s = mySettings->getString("lc");
  if(s != "") props.set(Controller_Left, s);
  s = mySettings->getString("rc");
  if(s != "") props.set(Controller_Right, s);
  s = mySettings->getString("bc");
  if(s != "") { props.set(Controller_Left, s); props.set(Controller_Right, s); }
  s = mySettings->getString("cp");
  if(s != "") props.set(Controller_SwapPaddles, s);
  s = mySettings->getString("format");
  if(s != "") props.set(Display_Format, s);
  s = mySettings->getString("ystart");
  if(s != "") props.set(Display_YStart, s);
  s = mySettings->getString("height");
  if(s != "") props.set(Display_Height, s);
  s = mySettings->getString("pp");
  if(s != "") props.set(Display_Phosphor, s);
  s = mySettings->getString("ppblend");
  if(s != "") props.set(Display_PPBlend, s);
  s = mySettings->getString("hmove");
  if(s != "") props.set(Emulation_HmoveBlanks, s);

  *cart = Cartridge::create(image, size, props, *mySettings);
  if(!*cart)
	return false;

  return true;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void OSystem::resetLoopTiming()
{
  memset(&myTimingInfo, 0, sizeof(TimingInfo));
  myTimingInfo.start = getTicks();
  myTimingInfo.virt = getTicks();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void OSystem::setDefaultJoymap()
{
  EventMode mode;

  mode = kEmulationMode;  // Default emulation events
  // Left joystick (assume joystick zero, button zero)
  myEventHandler->setDefaultJoyMapping(Event::JoystickZeroFire, mode, 0, 0);
  // Right joystick (assume joystick one, button zero)
  myEventHandler->setDefaultJoyMapping(Event::JoystickOneFire, mode, 1, 0);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void OSystem::setDefaultJoyAxisMap()
{
  EventMode mode;

  mode = kEmulationMode;  // Default emulation events
  // Left joystick left/right directions (assume joystick zero)
  myEventHandler->setDefaultJoyAxisMapping(Event::JoystickZeroLeft, mode, 0, 0, 0);
  myEventHandler->setDefaultJoyAxisMapping(Event::JoystickZeroRight, mode, 0, 0, 1);
  // Left joystick up/down directions (assume joystick zero)
  myEventHandler->setDefaultJoyAxisMapping(Event::JoystickZeroUp, mode, 0, 1, 0);
  myEventHandler->setDefaultJoyAxisMapping(Event::JoystickZeroDown, mode, 0, 1, 1);
  // Right joystick left/right directions (assume joystick one)
  myEventHandler->setDefaultJoyAxisMapping(Event::JoystickOneLeft, mode, 1, 0, 0);
  myEventHandler->setDefaultJoyAxisMapping(Event::JoystickOneRight, mode, 1, 0, 1);
  // Right joystick left/right directions (assume joystick one)
  myEventHandler->setDefaultJoyAxisMapping(Event::JoystickOneUp, mode, 1, 1, 0);
  myEventHandler->setDefaultJoyAxisMapping(Event::JoystickOneDown, mode, 1, 1, 1);

  mode = kMenuMode;  // Default menu/UI events
  myEventHandler->setDefaultJoyAxisMapping(Event::UILeft, mode, 0, 0, 0);
  myEventHandler->setDefaultJoyAxisMapping(Event::UIRight, mode, 0, 0, 1);
  myEventHandler->setDefaultJoyAxisMapping(Event::UIUp, mode, 0, 1, 0);
  myEventHandler->setDefaultJoyAxisMapping(Event::UIDown, mode, 0, 1, 1);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void OSystem::setDefaultJoyHatMap()
{
// FIXME - add emul and UI events
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void OSystem::pollEvent()
{
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool OSystem::joyButtonHandled(int button)
{
  // Since we don't do any platform-specific event polling,
  // no button is ever handled at this level
  return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void OSystem::stateChanged(EventHandler::State state)
{
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void OSystem::mainLoop()
{
  for(;;)
  {
	aiBase->update();  

	myTimingInfo.start = getTicks();
	myEventHandler->poll(myTimingInfo.start);
	if(myQuitLoop) break;  // Exit if the user wants to quit
	myFrameBuffer->update();
	myTimingInfo.current = getTicks();
	myTimingInfo.virt += myTimePerFrame;

	// Take out the artificial delays

	/*
	   if(myTimingInfo.current < myTimingInfo.virt)
	   {
			SDL_Delay((myTimingInfo.virt - myTimingInfo.current) / 1000);
	   }
	*/

	myTimingInfo.totalTime += (getTicks() - myTimingInfo.start);
	myTimingInfo.totalFrames++;

  }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void OSystem::queryVideoHardware()
{
  if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
	return;

  // First get the maximum windowed desktop resolution
  const SDL_VideoInfo* info = SDL_GetVideoInfo();
  myDesktopWidth  = info->current_w;
  myDesktopHeight = info->current_h;

  // Then get the valid fullscreen modes
  // If there are any errors, just use the desktop resolution
  ostringstream buf;
  SDL_Rect** modes = SDL_ListModes(NULL, SDL_FULLSCREEN);
  if((modes == (SDL_Rect**)0) || (modes == (SDL_Rect**)-1))
  {
	Resolution r;
	r.width  = myDesktopWidth;
	r.height = myDesktopHeight;
	buf << r.width << "x" << r.height;
	r.name = buf.str();
	myResolutions.push_back(r);
  }
  else
  {
	for(uInt32 i = 0; modes[i]; ++i)
	{
	  Resolution r;
	  r.width  = modes[i]->w;
	  r.height = modes[i]->h;
	  buf.str("");
	  buf << r.width << "x" << r.height;
	  r.name = buf.str();
	  myResolutions.insert_at(0, r);  // insert in opposite (of descending) order
	}
  }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
/*
  Palette is defined as follows:
	// Base colors
	kColor         TODO
	kBGColor       TODO
	kShadowColor      Item is disabled
	kTextColor        Normal text color
	kTextColorHi      Highlighted text color
	kTextColorEm   TODO

	// UI elements (dialog and widgets)
	kDlgColor         Dialog background
	kWidColor         Widget background
	kWidFrameColor    Border for currently selected widget

	// Button colors
	kBtnColor         Normal button background
	kBtnColorHi       Highlighted button background
	kBtnTextColor     Normal button font color
	kBtnTextColorHi   Highlighted button font color

	// Checkbox colors
	kCheckColor       Color of 'X' in checkbox

	// Scrollbar colors
	kScrollColor      Normal scrollbar color
	kScrollColorHi    Highlighted scrollbar color

	// Debugger colors
	kDbgChangedColor      Background color for changed cells
	kDbgChangedTextColor  Text color for changed cells
	kDbgColorHi           Highlighted color in debugger data cells
*/
uInt32 OSystem::ourGUIColors[kNumUIPalettes][kNumColors-256] = {
  // Standard
  { 0x686868, 0x000000, 0x404040, 0x000000, 0x62a108, 0x9f0000,
	0xc9af7c, 0xf0f0cf, 0xc80000,
	0xac3410, 0xd55941, 0xffffff, 0xffd652,
	0xac3410,
	0xac3410, 0xd55941,
	0xac3410, 0xd55941,
	0xc80000, 0x00ff00, 0xc8c8ff
  },

  // Classic
  { 0x686868, 0x000000, 0x404040, 0x20a020, 0x00ff00, 0xc80000,
	0x000000, 0x000000, 0xc80000,
	0x000000, 0x000000, 0x20a020, 0x00ff00,
	0x20a020,
	0x20a020, 0x00ff00,
	0x20a020, 0x00ff00,
	0xc80000, 0x00ff00, 0xc8c8ff
  }
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
OSystem::OSystem(const OSystem& osystem)
{
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
OSystem& OSystem::operator = (const OSystem&)
{
  assert(false);

  return *this;
}
