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
// $Id: StellaFont.hxx,v 1.7 2007/01/01 18:04:54 stephena Exp $
//
//   Based on code from ScummVM - Scumm Interpreter
//   Copyright (C) 2002-2004 The ScummVM project
//============================================================================

#ifndef STELLA_FONT_DATA_HXX
#define STELLA_FONT_DATA_HXX

#include "Font.hxx"
#include "bspf.hxx"

namespace GUI {

/* Generated by convbdf on Sun Aug 15 15:59:36 2004. */
/* Font information:
   name: 04b-16b-10
   facename: 04b-16b-10
   w x h: 9x10
   size: 94
   ascent: 8
   descent: 2
   first char: 33 (0x21)
   last char: 126 (0x7e)
   default char: 33 (0x21)
   proportional: yes
   
*/

/* Font character bitmap data. */
static const uInt16 _stella_font_bits[] = {

/* Character 33 (0x21):
   width 3
   +---+
   |   |
   | * |
   | * |
   | * |
   | * |
   | * |
   |   |
   | * |
   |   |
   |   |
   +---+
*/
0x0000,
0x4000,
0x4000,
0x4000,
0x4000,
0x4000,
0x0000,
0x4000,
0x0000,
0x0000,

/* Character 34 (0x22):
   width 4
   +----+
   |    |
   |* * |
   |* * |
   |    |
   |    |
   |    |
   |    |
   |    |
   |    |
   |    |
   +----+
*/
0x0000,
0xa000,
0xa000,
0x0000,
0x0000,
0x0000,
0x0000,
0x0000,
0x0000,
0x0000,

/* Character 35 (0x23):
   width 6
   +------+
   |      |
   |      |
   | * *  |
   |***** |
   | * *  |
   |***** |
   | * *  |
   |      |
   |      |
   |      |
   +------+
*/
0x0000,
0x0000,
0x5000,
0xf800,
0x5000,
0xf800,
0x5000,
0x0000,
0x0000,
0x0000,

/* Character 36 (0x24):
   width 6
   +------+
   |  *   |
   | ***  |
   |* * * |
   |* *   |
   | ***  |
   |  * * |
   |* * * |
   | ***  |
   |  *   |
   |      |
   +------+
*/
0x2000,
0x7000,
0xa800,
0xa000,
0x7000,
0x2800,
0xa800,
0x7000,
0x2000,
0x0000,

/* Character 37 (0x25):
   width 9
   +---------+
   |         |
   | *   *   |
   |* *  *   |
   |* * *    |
   | *  *    |
   |   *  *  |
   |   * * * |
   |  *  * * |
   |  *   *  |
   |         |
   +---------+
*/
0x0000,
0x4400,
0xa400,
0xa800,
0x4800,
0x1200,
0x1500,
0x2500,
0x2200,
0x0000,

/* Character 38 (0x26):
   width 5
   +-----+
   |     |
   | **  |
   |*    |
   |* *  |
   | *** |
   |* *  |
   |* *  |
   | * * |
   |     |
   |     |
   +-----+
*/
0x0000,
0x6000,
0x8000,
0xa000,
0x7000,
0xa000,
0xa000,
0x5000,
0x0000,
0x0000,

/* Character 39 (0x27):
   width 2
   +--+
   |  |
   |* |
   |* |
   |  |
   |  |
   |  |
   |  |
   |  |
   |  |
   |  |
   +--+
*/
0x0000,
0x8000,
0x8000,
0x0000,
0x0000,
0x0000,
0x0000,
0x0000,
0x0000,
0x0000,

/* Character 40 (0x28):
   width 5
   +-----+
   |     |
   |   * |
   |  *  |
   | *   |
   | *   |
   | *   |
   |  *  |
   |   * |
   |     |
   |     |
   +-----+
*/
0x0000,
0x1000,
0x2000,
0x4000,
0x4000,
0x4000,
0x2000,
0x1000,
0x0000,
0x0000,

/* Character 41 (0x29):
   width 5
   +-----+
   |     |
   |*    |
   | *   |
   |  *  |
   |  *  |
   |  *  |
   | *   |
   |*    |
   |     |
   |     |
   +-----+
*/
0x0000,
0x8000,
0x4000,
0x2000,
0x2000,
0x2000,
0x4000,
0x8000,
0x0000,
0x0000,

/* Character 42 (0x2a):
   width 6
   +------+
   |      |
   |      |
   |  *   |
   |* * * |
   | ***  |
   |* * * |
   |  *   |
   |      |
   |      |
   |      |
   +------+
*/
0x0000,
0x0000,
0x2000,
0xa800,
0x7000,
0xa800,
0x2000,
0x0000,
0x0000,
0x0000,

/* Character 43 (0x2b):
   width 6
   +------+
   |      |
   |      |
   |  *   |
   |  *   |
   |***** |
   |  *   |
   |  *   |
   |      |
   |      |
   |      |
   +------+
*/
0x0000,
0x0000,
0x2000,
0x2000,
0xf800,
0x2000,
0x2000,
0x0000,
0x0000,
0x0000,

/* Character 44 (0x2c):
   width 3
   +---+
   |   |
   |   |
   |   |
   |   |
   |   |
   |   |
   | * |
   | * |
   |*  |
   |   |
   +---+
*/
0x0000,
0x0000,
0x0000,
0x0000,
0x0000,
0x0000,
0x4000,
0x4000,
0x8000,
0x0000,

/* Character 45 (0x2d):
   width 5
   +-----+
   |     |
   |     |
   |     |
   |     |
   |**** |
   |     |
   |     |
   |     |
   |     |
   |     |
   +-----+
*/
0x0000,
0x0000,
0x0000,
0x0000,
0xf000,
0x0000,
0x0000,
0x0000,
0x0000,
0x0000,

/* Character 46 (0x2e):
   width 2
   +--+
   |  |
   |  |
   |  |
   |  |
   |  |
   |  |
   |  |
   |* |
   |  |
   |  |
   +--+
*/
0x0000,
0x0000,
0x0000,
0x0000,
0x0000,
0x0000,
0x0000,
0x8000,
0x0000,
0x0000,

/* Character 47 (0x2f):
   width 5
   +-----+
   |     |
   |   * |
   |   * |
   |  *  |
   |  *  |
   | *   |
   | *   |
   |*    |
   |*    |
   |     |
   +-----+
*/
0x0000,
0x1000,
0x1000,
0x2000,
0x2000,
0x4000,
0x4000,
0x8000,
0x8000,
0x0000,

/* Character 48 (0x30):
   width 5
   +-----+
   |     |
   | **  |
   |*  * |
   |*  * |
   |*  * |
   |*  * |
   |*  * |
   | **  |
   |     |
   |     |
   +-----+
*/
0x0000,
0x6000,
0x9000,
0x9000,
0x9000,
0x9000,
0x9000,
0x6000,
0x0000,
0x0000,

/* Character 49 (0x31):
   width 3
   +---+
   |   |
   | * |
   |** |
   | * |
   | * |
   | * |
   | * |
   | * |
   |   |
   |   |
   +---+
*/
0x0000,
0x4000,
0xc000,
0x4000,
0x4000,
0x4000,
0x4000,
0x4000,
0x0000,
0x0000,

/* Character 50 (0x32):
   width 5
   +-----+
   |     |
   |***  |
   |   * |
   |   * |
   |  *  |
   | *   |
   |*    |
   |**** |
   |     |
   |     |
   +-----+
*/
0x0000,
0xe000,
0x1000,
0x1000,
0x2000,
0x4000,
0x8000,
0xf000,
0x0000,
0x0000,

/* Character 51 (0x33):
   width 5
   +-----+
   |     |
   |***  |
   |   * |
   |   * |
   | **  |
   |   * |
   |   * |
   |***  |
   |     |
   |     |
   +-----+
*/
0x0000,
0xe000,
0x1000,
0x1000,
0x6000,
0x1000,
0x1000,
0xe000,
0x0000,
0x0000,

/* Character 52 (0x34):
   width 5
   +-----+
   |     |
   |  *  |
   | **  |
   |* *  |
   |* *  |
   |**** |
   |  *  |
   |  *  |
   |     |
   |     |
   +-----+
*/
0x0000,
0x2000,
0x6000,
0xa000,
0xa000,
0xf000,
0x2000,
0x2000,
0x0000,
0x0000,

/* Character 53 (0x35):
   width 5
   +-----+
   |     |
   |**** |
   |*    |
   |***  |
   |   * |
   |   * |
   |   * |
   |***  |
   |     |
   |     |
   +-----+
*/
0x0000,
0xf000,
0x8000,
0xe000,
0x1000,
0x1000,
0x1000,
0xe000,
0x0000,
0x0000,

/* Character 54 (0x36):
   width 5
   +-----+
   |     |
   | **  |
   |*    |
   |***  |
   |*  * |
   |*  * |
   |*  * |
   | **  |
   |     |
   |     |
   +-----+
*/
0x0000,
0x6000,
0x8000,
0xe000,
0x9000,
0x9000,
0x9000,
0x6000,
0x0000,
0x0000,

/* Character 55 (0x37):
   width 5
   +-----+
   |     |
   |**** |
   |   * |
   |   * |
   |  *  |
   |  *  |
   | *   |
   | *   |
   |     |
   |     |
   +-----+
*/
0x0000,
0xf000,
0x1000,
0x1000,
0x2000,
0x2000,
0x4000,
0x4000,
0x0000,
0x0000,

/* Character 56 (0x38):
   width 5
   +-----+
   |     |
   | **  |
   |*  * |
   |*  * |
   | **  |
   |*  * |
   |*  * |
   | **  |
   |     |
   |     |
   +-----+
*/
0x0000,
0x6000,
0x9000,
0x9000,
0x6000,
0x9000,
0x9000,
0x6000,
0x0000,
0x0000,

/* Character 57 (0x39):
   width 5
   +-----+
   |     |
   | **  |
   |*  * |
   |*  * |
   |*  * |
   | *** |
   |   * |
   | **  |
   |     |
   |     |
   +-----+
*/
0x0000,
0x6000,
0x9000,
0x9000,
0x9000,
0x7000,
0x1000,
0x6000,
0x0000,
0x0000,

/* Character 58 (0x3a):
   width 2
   +--+
   |  |
   |  |
   |  |
   |* |
   |  |
   |* |
   |  |
   |  |
   |  |
   |  |
   +--+
*/
0x0000,
0x0000,
0x0000,
0x8000,
0x0000,
0x8000,
0x0000,
0x0000,
0x0000,
0x0000,

/* Character 59 (0x3b):
   width 2
   +--+
   |  |
   |  |
   |  |
   |* |
   |  |
   |* |
   |* |
   |  |
   |  |
   |  |
   +--+
*/
0x0000,
0x0000,
0x0000,
0x8000,
0x0000,
0x8000,
0x8000,
0x0000,
0x0000,
0x0000,

/* Character 60 (0x3c):
   width 5
   +-----+
   |     |
   |     |
   |   * |
   |  *  |
   | *   |
   |  *  |
   |   * |
   |     |
   |     |
   |     |
   +-----+
*/
0x0000,
0x0000,
0x1000,
0x2000,
0x4000,
0x2000,
0x1000,
0x0000,
0x0000,
0x0000,

/* Character 61 (0x3d):
   width 5
   +-----+
   |     |
   |     |
   |     |
   |**** |
   |     |
   |**** |
   |     |
   |     |
   |     |
   |     |
   +-----+
*/
0x0000,
0x0000,
0x0000,
0xf000,
0x0000,
0xf000,
0x0000,
0x0000,
0x0000,
0x0000,

/* Character 62 (0x3e):
   width 5
   +-----+
   |     |
   |     |
   |*    |
   | *   |
   |  *  |
   | *   |
   |*    |
   |     |
   |     |
   |     |
   +-----+
*/
0x0000,
0x0000,
0x8000,
0x4000,
0x2000,
0x4000,
0x8000,
0x0000,
0x0000,
0x0000,

/* Character 63 (0x3f):
   width 5
   +-----+
   |     |
   |***  |
   |   * |
   |   * |
   |  *  |
   | *   |
   |     |
   | *   |
   |     |
   |     |
   +-----+
*/
0x0000,
0xe000,
0x1000,
0x1000,
0x2000,
0x4000,
0x0000,
0x4000,
0x0000,
0x0000,

/* Character 64 (0x40):
   width 7
   +-------+
   |       |
   |  ***  |
   | *   * |
   |*  *** |
   |* *  * |
   |*  *** |
   | *     |
   |  **** |
   |       |
   |       |
   +-------+
*/
0x0000,
0x3800,
0x4400,
0x9c00,
0xa400,
0x9c00,
0x4000,
0x3c00,
0x0000,
0x0000,

/* Character 65 (0x41):
   width 5
   +-----+
   |     |
   | **  |
   |*  * |
   |**** |
   |*  * |
   |*  * |
   |*  * |
   |*  * |
   |     |
   |     |
   +-----+
*/
0x0000,
0x6000,
0x9000,
0xf000,
0x9000,
0x9000,
0x9000,
0x9000,
0x0000,
0x0000,

/* Character 66 (0x42):
   width 5
   +-----+
   |     |
   |***  |
   |*  * |
   |***  |
   |*  * |
   |*  * |
   |*  * |
   |***  |
   |     |
   |     |
   +-----+
*/
0x0000,
0xe000,
0x9000,
0xe000,
0x9000,
0x9000,
0x9000,
0xe000,
0x0000,
0x0000,

/* Character 67 (0x43):
   width 5
   +-----+
   |     |
   | **  |
   |*  * |
   |*    |
   |*    |
   |*    |
   |*  * |
   | **  |
   |     |
   |     |
   +-----+
*/
0x0000,
0x6000,
0x9000,
0x8000,
0x8000,
0x8000,
0x9000,
0x6000,
0x0000,
0x0000,

/* Character 68 (0x44):
   width 5
   +-----+
   |     |
   |***  |
   |*  * |
   |*  * |
   |*  * |
   |*  * |
   |*  * |
   |***  |
   |     |
   |     |
   +-----+
*/
0x0000,
0xe000,
0x9000,
0x9000,
0x9000,
0x9000,
0x9000,
0xe000,
0x0000,
0x0000,

/* Character 69 (0x45):
   width 5
   +-----+
   |     |
   |**** |
   |*    |
   |**** |
   |*    |
   |*    |
   |*    |
   |**** |
   |     |
   |     |
   +-----+
*/
0x0000,
0xf000,
0x8000,
0xf000,
0x8000,
0x8000,
0x8000,
0xf000,
0x0000,
0x0000,

/* Character 70 (0x46):
   width 5
   +-----+
   |     |
   |**** |
   |*    |
   |**** |
   |*    |
   |*    |
   |*    |
   |*    |
   |     |
   |     |
   +-----+
*/
0x0000,
0xf000,
0x8000,
0xf000,
0x8000,
0x8000,
0x8000,
0x8000,
0x0000,
0x0000,

/* Character 71 (0x47):
   width 5
   +-----+
   |     |
   | **  |
   |*  * |
   |*    |
   |* ** |
   |*  * |
   |*  * |
   | **  |
   |     |
   |     |
   +-----+
*/
0x0000,
0x6000,
0x9000,
0x8000,
0xb000,
0x9000,
0x9000,
0x6000,
0x0000,
0x0000,

/* Character 72 (0x48):
   width 5
   +-----+
   |     |
   |*  * |
   |*  * |
   |**** |
   |*  * |
   |*  * |
   |*  * |
   |*  * |
   |     |
   |     |
   +-----+
*/
0x0000,
0x9000,
0x9000,
0xf000,
0x9000,
0x9000,
0x9000,
0x9000,
0x0000,
0x0000,

/* Character 73 (0x49):
   width 2
   +--+
   |  |
   |* |
   |* |
   |* |
   |* |
   |* |
   |* |
   |* |
   |  |
   |  |
   +--+
*/
0x0000,
0x8000,
0x8000,
0x8000,
0x8000,
0x8000,
0x8000,
0x8000,
0x0000,
0x0000,

/* Character 74 (0x4a):
   width 5
   +-----+
   |     |
   |  ** |
   |   * |
   |   * |
   |*  * |
   |*  * |
   |*  * |
   | **  |
   |     |
   |     |
   +-----+
*/
0x0000,
0x3000,
0x1000,
0x1000,
0x9000,
0x9000,
0x9000,
0x6000,
0x0000,
0x0000,

/* Character 75 (0x4b):
   width 5
   +-----+
   |     |
   |*  * |
   |*  * |
   |* *  |
   |**   |
   |* *  |
   |*  * |
   |*  * |
   |     |
   |     |
   +-----+
*/
0x0000,
0x9000,
0x9000,
0xa000,
0xc000,
0xa000,
0x9000,
0x9000,
0x0000,
0x0000,

/* Character 76 (0x4c):
   width 5
   +-----+
   |     |
   |*    |
   |*    |
   |*    |
   |*    |
   |*    |
   |*    |
   | *** |
   |     |
   |     |
   +-----+
*/
0x0000,
0x8000,
0x8000,
0x8000,
0x8000,
0x8000,
0x8000,
0x7000,
0x0000,
0x0000,

/* Character 77 (0x4d):
   width 6
   +------+
   |      |
   |*   * |
   |** ** |
   |* * * |
   |*   * |
   |*   * |
   |*   * |
   |*   * |
   |      |
   |      |
   +------+
*/
0x0000,
0x8800,
0xd800,
0xa800,
0x8800,
0x8800,
0x8800,
0x8800,
0x0000,
0x0000,

/* Character 78 (0x4e):
   width 5
   +-----+
   |     |
   |*  * |
   |** * |
   |* ** |
   |*  * |
   |*  * |
   |*  * |
   |*  * |
   |     |
   |     |
   +-----+
*/
0x0000,
0x9000,
0xd000,
0xb000,
0x9000,
0x9000,
0x9000,
0x9000,
0x0000,
0x0000,

/* Character 79 (0x4f):
   width 5
   +-----+
   |     |
   | **  |
   |*  * |
   |*  * |
   |*  * |
   |*  * |
   |*  * |
   | **  |
   |     |
   |     |
   +-----+
*/
0x0000,
0x6000,
0x9000,
0x9000,
0x9000,
0x9000,
0x9000,
0x6000,
0x0000,
0x0000,

/* Character 80 (0x50):
   width 5
   +-----+
   |     |
   |***  |
   |*  * |
   |*  * |
   |***  |
   |*    |
   |*    |
   |*    |
   |     |
   |     |
   +-----+
*/
0x0000,
0xe000,
0x9000,
0x9000,
0xe000,
0x8000,
0x8000,
0x8000,
0x0000,
0x0000,

/* Character 81 (0x51):
   width 5
   +-----+
   |     |
   | **  |
   |*  * |
   |*  * |
   |*  * |
   |*  * |
   |*  * |
   | **  |
   |   * |
   |     |
   +-----+
*/
0x0000,
0x6000,
0x9000,
0x9000,
0x9000,
0x9000,
0x9000,
0x6000,
0x1000,
0x0000,

/* Character 82 (0x52):
   width 5
   +-----+
   |     |
   |***  |
   |*  * |
   |*  * |
   |***  |
   |*  * |
   |*  * |
   |*  * |
   |     |
   |     |
   +-----+
*/
0x0000,
0xe000,
0x9000,
0x9000,
0xe000,
0x9000,
0x9000,
0x9000,
0x0000,
0x0000,

/* Character 83 (0x53):
   width 5
   +-----+
   |     |
   | **  |
   |*  * |
   |*    |
   | **  |
   |   * |
   |*  * |
   | **  |
   |     |
   |     |
   +-----+
*/
0x0000,
0x6000,
0x9000,
0x8000,
0x6000,
0x1000,
0x9000,
0x6000,
0x0000,
0x0000,

/* Character 84 (0x54):
   width 6
   +------+
   |      |
   |***** |
   |  *   |
   |  *   |
   |  *   |
   |  *   |
   |  *   |
   |  *   |
   |      |
   |      |
   +------+
*/
0x0000,
0xf800,
0x2000,
0x2000,
0x2000,
0x2000,
0x2000,
0x2000,
0x0000,
0x0000,

/* Character 85 (0x55):
   width 5
   +-----+
   |     |
   |*  * |
   |*  * |
   |*  * |
   |*  * |
   |*  * |
   |*  * |
   | **  |
   |     |
   |     |
   +-----+
*/
0x0000,
0x9000,
0x9000,
0x9000,
0x9000,
0x9000,
0x9000,
0x6000,
0x0000,
0x0000,

/* Character 86 (0x56):
   width 6
   +------+
   |      |
   |*   * |
   |*   * |
   |*   * |
   | * *  |
   | * *  |
   |  *   |
   |  *   |
   |      |
   |      |
   +------+
*/
0x0000,
0x8800,
0x8800,
0x8800,
0x5000,
0x5000,
0x2000,
0x2000,
0x0000,
0x0000,

/* Character 87 (0x57):
   width 6
   +------+
   |      |
   |*   * |
   |*   * |
   |*   * |
   |* * * |
   |* * * |
   | * *  |
   | * *  |
   |      |
   |      |
   +------+
*/
0x0000,
0x8800,
0x8800,
0x8800,
0xa800,
0xa800,
0x5000,
0x5000,
0x0000,
0x0000,

/* Character 88 (0x58):
   width 5
   +-----+
   |     |
   |*  * |
   |*  * |
   | **  |
   |*  * |
   |*  * |
   |*  * |
   |*  * |
   |     |
   |     |
   +-----+
*/
0x0000,
0x9000,
0x9000,
0x6000,
0x9000,
0x9000,
0x9000,
0x9000,
0x0000,
0x0000,

/* Character 89 (0x59):
   width 6
   +------+
   |      |
   |*   * |
   |*   * |
   | * *  |
   |  *   |
   |  *   |
   |  *   |
   |  *   |
   |      |
   |      |
   +------+
*/
0x0000,
0x8800,
0x8800,
0x5000,
0x2000,
0x2000,
0x2000,
0x2000,
0x0000,
0x0000,

/* Character 90 (0x5a):
   width 5
   +-----+
   |     |
   |**** |
   |   * |
   |  *  |
   | *   |
   |*    |
   |*    |
   |**** |
   |     |
   |     |
   +-----+
*/
0x0000,
0xf000,
0x1000,
0x2000,
0x4000,
0x8000,
0x8000,
0xf000,
0x0000,
0x0000,

/* Character 91 (0x5b):
   width 4
   +----+
   |    |
   | ** |
   | *  |
   | *  |
   | *  |
   | *  |
   | *  |
   | ** |
   |    |
   |    |
   +----+
*/
0x0000,
0x6000,
0x4000,
0x4000,
0x4000,
0x4000,
0x4000,
0x6000,
0x0000,
0x0000,

/* Character 92 (0x5c):
   width 5
   +-----+
   |     |
   |*    |
   |*    |
   | *   |
   | *   |
   |  *  |
   |  *  |
   |   * |
   |   * |
   |     |
   +-----+
*/
0x0000,
0x8000,
0x8000,
0x4000,
0x4000,
0x2000,
0x2000,
0x1000,
0x1000,
0x0000,

/* Character 93 (0x5d):
   width 4
   +----+
   |    |
   |**  |
   | *  |
   | *  |
   | *  |
   | *  |
   | *  |
   |**  |
   |    |
   |    |
   +----+
*/
0x0000,
0xc000,
0x4000,
0x4000,
0x4000,
0x4000,
0x4000,
0xc000,
0x0000,
0x0000,

/* Character 94 (0x5e):
   width 4
   +----+
   |    |
   | *  |
   |* * |
   |    |
   |    |
   |    |
   |    |
   |    |
   |    |
   |    |
   +----+
*/
0x0000,
0x4000,
0xa000,
0x0000,
0x0000,
0x0000,
0x0000,
0x0000,
0x0000,
0x0000,

/* Character 95 (0x5f):
   width 5
   +-----+
   |     |
   |     |
   |     |
   |     |
   |     |
   |     |
   |     |
   |**** |
   |     |
   |     |
   +-----+
*/
0x0000,
0x0000,
0x0000,
0x0000,
0x0000,
0x0000,
0x0000,
0xf000,
0x0000,
0x0000,

/* Character 96 (0x60):
   width 3
   +---+
   |   |
   |*  |
   | * |
   |   |
   |   |
   |   |
   |   |
   |   |
   |   |
   |   |
   +---+
*/
0x0000,
0x8000,
0x4000,
0x0000,
0x0000,
0x0000,
0x0000,
0x0000,
0x0000,
0x0000,

/* Character 97 (0x61):
   width 5
   +-----+
   |     |
   |     |
   |     |
   | *** |
   |*  * |
   |*  * |
   |*  * |
   | *** |
   |     |
   |     |
   +-----+
*/
0x0000,
0x0000,
0x0000,
0x7000,
0x9000,
0x9000,
0x9000,
0x7000,
0x0000,
0x0000,

/* Character 98 (0x62):
   width 5
   +-----+
   |     |
   |*    |
   |*    |
   |***  |
   |*  * |
   |*  * |
   |*  * |
   |***  |
   |     |
   |     |
   +-----+
*/
0x0000,
0x8000,
0x8000,
0xe000,
0x9000,
0x9000,
0x9000,
0xe000,
0x0000,
0x0000,

/* Character 99 (0x63):
   width 4
   +----+
   |    |
   |    |
   |    |
   | ** |
   |*   |
   |*   |
   |*   |
   | ** |
   |    |
   |    |
   +----+
*/
0x0000,
0x0000,
0x0000,
0x6000,
0x8000,
0x8000,
0x8000,
0x6000,
0x0000,
0x0000,

/* Character 100 (0x64):
   width 5
   +-----+
   |     |
   |   * |
   |   * |
   | *** |
   |*  * |
   |*  * |
   |*  * |
   | *** |
   |     |
   |     |
   +-----+
*/
0x0000,
0x1000,
0x1000,
0x7000,
0x9000,
0x9000,
0x9000,
0x7000,
0x0000,
0x0000,

/* Character 101 (0x65):
   width 5
   +-----+
   |     |
   |     |
   |     |
   | **  |
   |*  * |
   |**** |
   |*    |
   | **  |
   |     |
   |     |
   +-----+
*/
0x0000,
0x0000,
0x0000,
0x6000,
0x9000,
0xf000,
0x8000,
0x6000,
0x0000,
0x0000,

/* Character 102 (0x66):
   width 5
   +-----+
   |     |
   |  ** |
   | *   |
   |**** |
   | *   |
   | *   |
   | *   |
   | *   |
   |     |
   |     |
   +-----+
*/
0x0000,
0x3000,
0x4000,
0xf000,
0x4000,
0x4000,
0x4000,
0x4000,
0x0000,
0x0000,

/* Character 103 (0x67):
   width 5
   +-----+
   |     |
   |     |
   |     |
   | *** |
   |*  * |
   |*  * |
   |*  * |
   | *** |
   |   * |
   | **  |
   +-----+
*/
0x0000,
0x0000,
0x0000,
0x7000,
0x9000,
0x9000,
0x9000,
0x7000,
0x1000,
0x6000,

/* Character 104 (0x68):
   width 5
   +-----+
   |     |
   |*    |
   |*    |
   |***  |
   |*  * |
   |*  * |
   |*  * |
   |*  * |
   |     |
   |     |
   +-----+
*/
0x0000,
0x8000,
0x8000,
0xe000,
0x9000,
0x9000,
0x9000,
0x9000,
0x0000,
0x0000,

/* Character 105 (0x69):
   width 2
   +--+
   |  |
   |* |
   |  |
   |* |
   |* |
   |* |
   |* |
   |* |
   |  |
   |  |
   +--+
*/
0x0000,
0x8000,
0x0000,
0x8000,
0x8000,
0x8000,
0x8000,
0x8000,
0x0000,
0x0000,

/* Character 106 (0x6a):
   width 4
   +----+
   |    |
   |  * |
   |    |
   |  * |
   |  * |
   |  * |
   |  * |
   |  * |
   |  * |
   |**  |
   +----+
*/
0x0000,
0x2000,
0x0000,
0x2000,
0x2000,
0x2000,
0x2000,
0x2000,
0x2000,
0xc000,

/* Character 107 (0x6b):
   width 5
   +-----+
   |     |
   |*    |
   |*    |
   |*  * |
   |* *  |
   |**   |
   |* *  |
   |*  * |
   |     |
   |     |
   +-----+
*/
0x0000,
0x8000,
0x8000,
0x9000,
0xa000,
0xc000,
0xa000,
0x9000,
0x0000,
0x0000,

/* Character 108 (0x6c):
   width 2
   +--+
   |  |
   |* |
   |* |
   |* |
   |* |
   |* |
   |* |
   |* |
   |  |
   |  |
   +--+
*/
0x0000,
0x8000,
0x8000,
0x8000,
0x8000,
0x8000,
0x8000,
0x8000,
0x0000,
0x0000,

/* Character 109 (0x6d):
   width 6
   +------+
   |      |
   |      |
   |      |
   |****  |
   |* * * |
   |* * * |
   |* * * |
   |* * * |
   |      |
   |      |
   +------+
*/
0x0000,
0x0000,
0x0000,
0xf000,
0xa800,
0xa800,
0xa800,
0xa800,
0x0000,
0x0000,

/* Character 110 (0x6e):
   width 5
   +-----+
   |     |
   |     |
   |     |
   |***  |
   |*  * |
   |*  * |
   |*  * |
   |*  * |
   |     |
   |     |
   +-----+
*/
0x0000,
0x0000,
0x0000,
0xe000,
0x9000,
0x9000,
0x9000,
0x9000,
0x0000,
0x0000,

/* Character 111 (0x6f):
   width 5
   +-----+
   |     |
   |     |
   |     |
   | **  |
   |*  * |
   |*  * |
   |*  * |
   | **  |
   |     |
   |     |
   +-----+
*/
0x0000,
0x0000,
0x0000,
0x6000,
0x9000,
0x9000,
0x9000,
0x6000,
0x0000,
0x0000,

/* Character 112 (0x70):
   width 5
   +-----+
   |     |
   |     |
   |     |
   |***  |
   |*  * |
   |*  * |
   |*  * |
   |***  |
   |*    |
   |*    |
   +-----+
*/
0x0000,
0x0000,
0x0000,
0xe000,
0x9000,
0x9000,
0x9000,
0xe000,
0x8000,
0x8000,

/* Character 113 (0x71):
   width 5
   +-----+
   |     |
   |     |
   |     |
   | *** |
   |*  * |
   |*  * |
   |*  * |
   | *** |
   |   * |
   |   * |
   +-----+
*/
0x0000,
0x0000,
0x0000,
0x7000,
0x9000,
0x9000,
0x9000,
0x7000,
0x1000,
0x1000,

/* Character 114 (0x72):
   width 5
   +-----+
   |     |
   |     |
   |     |
   |* ** |
   |**   |
   |*    |
   |*    |
   |*    |
   |     |
   |     |
   +-----+
*/
0x0000,
0x0000,
0x0000,
0xb000,
0xc000,
0x8000,
0x8000,
0x8000,
0x0000,
0x0000,

/* Character 115 (0x73):
   width 5
   +-----+
   |     |
   |     |
   |     |
   | *** |
   |*    |
   | **  |
   |   * |
   |***  |
   |     |
   |     |
   +-----+
*/
0x0000,
0x0000,
0x0000,
0x7000,
0x8000,
0x6000,
0x1000,
0xe000,
0x0000,
0x0000,

/* Character 116 (0x74):
   width 4
   +----+
   |    |
   | *  |
   | *  |
   |*** |
   | *  |
   | *  |
   | *  |
   |  * |
   |    |
   |    |
   +----+
*/
0x0000,
0x4000,
0x4000,
0xe000,
0x4000,
0x4000,
0x4000,
0x2000,
0x0000,
0x0000,

/* Character 117 (0x75):
   width 5
   +-----+
   |     |
   |     |
   |     |
   |*  * |
   |*  * |
   |*  * |
   |*  * |
   | *** |
   |     |
   |     |
   +-----+
*/
0x0000,
0x0000,
0x0000,
0x9000,
0x9000,
0x9000,
0x9000,
0x7000,
0x0000,
0x0000,

/* Character 118 (0x76):
   width 6
   +------+
   |      |
   |      |
   |      |
   |*   * |
   |*   * |
   | * *  |
   | * *  |
   |  *   |
   |      |
   |      |
   +------+
*/
0x0000,
0x0000,
0x0000,
0x8800,
0x8800,
0x5000,
0x5000,
0x2000,
0x0000,
0x0000,

/* Character 119 (0x77):
   width 6
   +------+
   |      |
   |      |
   |      |
   |* * * |
   |* * * |
   |* * * |
   | * *  |
   | * *  |
   |      |
   |      |
   +------+
*/
0x0000,
0x0000,
0x0000,
0xa800,
0xa800,
0xa800,
0x5000,
0x5000,
0x0000,
0x0000,

/* Character 120 (0x78):
   width 5
   +-----+
   |     |
   |     |
   |     |
   |*  * |
   |*  * |
   | **  |
   |*  * |
   |*  * |
   |     |
   |     |
   +-----+
*/
0x0000,
0x0000,
0x0000,
0x9000,
0x9000,
0x6000,
0x9000,
0x9000,
0x0000,
0x0000,

/* Character 121 (0x79):
   width 5
   +-----+
   |     |
   |     |
   |     |
   |*  * |
   |*  * |
   |*  * |
   |*  * |
   | *** |
   |   * |
   | **  |
   +-----+
*/
0x0000,
0x0000,
0x0000,
0x9000,
0x9000,
0x9000,
0x9000,
0x7000,
0x1000,
0x6000,

/* Character 122 (0x7a):
   width 5
   +-----+
   |     |
   |     |
   |     |
   |**** |
   |   * |
   | **  |
   |*    |
   |**** |
   |     |
   |     |
   +-----+
*/
0x0000,
0x0000,
0x0000,
0xf000,
0x1000,
0x6000,
0x8000,
0xf000,
0x0000,
0x0000,

/* Character 123 (0x7b):
   width 5
   +-----+
   |   * |
   |  *  |
   |  *  |
   |  *  |
   | *   |
   |  *  |
   |  *  |
   |  *  |
   |   * |
   |     |
   +-----+
*/
0x1000,
0x2000,
0x2000,
0x2000,
0x4000,
0x2000,
0x2000,
0x2000,
0x1000,
0x0000,

/* Character 124 (0x7c):
   width 4
   +----+
   |    |
   | *  |
   | *  |
   | *  |
   | *  |
   | *  |
   | *  |
   | *  |
   | *  |
   |    |
   +----+
*/
0x0000,
0x4000,
0x4000,
0x4000,
0x4000,
0x4000,
0x4000,
0x4000,
0x4000,
0x0000,

/* Character 125 (0x7d):
   width 5
   +-----+
   |*    |
   | *   |
   | *   |
   | *   |
   |  *  |
   | *   |
   | *   |
   | *   |
   |*    |
   |     |
   +-----+
*/
0x8000,
0x4000,
0x4000,
0x4000,
0x2000,
0x4000,
0x4000,
0x4000,
0x8000,
0x0000,

/* Character 126 (0x7e):
   width 5
   +-----+
   |     |
   | * * |
   |* *  |
   |     |
   |     |
   |     |
   |     |
   |     |
   |     |
   |     |
   +-----+
*/
0x0000,
0x5000,
0xa000,
0x0000,
0x0000,
0x0000,
0x0000,
0x0000,
0x0000,
0x0000,
};

/* Character width data. */
static const unsigned char _stella_sysfont_width[] = {
	3,	/* (0x21) */
	4,	/* (0x22) */
	6,	/* (0x23) */
	6,	/* (0x24) */
	9,	/* (0x25) */
	5,	/* (0x26) */
	2,	/* (0x27) */
	5,	/* (0x28) */
	5,	/* (0x29) */
	6,	/* (0x2a) */
	6,	/* (0x2b) */
	3,	/* (0x2c) */
	5,	/* (0x2d) */
	2,	/* (0x2e) */
	5,	/* (0x2f) */
	5,	/* (0x30) */
	3,	/* (0x31) */
	5,	/* (0x32) */
	5,	/* (0x33) */
	5,	/* (0x34) */
	5,	/* (0x35) */
	5,	/* (0x36) */
	5,	/* (0x37) */
	5,	/* (0x38) */
	5,	/* (0x39) */
	2,	/* (0x3a) */
	2,	/* (0x3b) */
	5,	/* (0x3c) */
	5,	/* (0x3d) */
	5,	/* (0x3e) */
	5,	/* (0x3f) */
	7,	/* (0x40) */
	5,	/* (0x41) */
	5,	/* (0x42) */
	5,	/* (0x43) */
	5,	/* (0x44) */
	5,	/* (0x45) */
	5,	/* (0x46) */
	5,	/* (0x47) */
	5,	/* (0x48) */
	2,	/* (0x49) */
	5,	/* (0x4a) */
	5,	/* (0x4b) */
	5,	/* (0x4c) */
	6,	/* (0x4d) */
	5,	/* (0x4e) */
	5,	/* (0x4f) */
	5,	/* (0x50) */
	5,	/* (0x51) */
	5,	/* (0x52) */
	5,	/* (0x53) */
	6,	/* (0x54) */
	5,	/* (0x55) */
	6,	/* (0x56) */
	6,	/* (0x57) */
	5,	/* (0x58) */
	6,	/* (0x59) */
	5,	/* (0x5a) */
	4,	/* (0x5b) */
	5,	/* (0x5c) */
	4,	/* (0x5d) */
	4,	/* (0x5e) */
	5,	/* (0x5f) */
	3,	/* (0x60) */
	5,	/* (0x61) */
	5,	/* (0x62) */
	4,	/* (0x63) */
	5,	/* (0x64) */
	5,	/* (0x65) */
	5,	/* (0x66) */
	5,	/* (0x67) */
	5,	/* (0x68) */
	2,	/* (0x69) */
	4,	/* (0x6a) */
	5,	/* (0x6b) */
	2,	/* (0x6c) */
	6,	/* (0x6d) */
	5,	/* (0x6e) */
	5,	/* (0x6f) */
	5,	/* (0x70) */
	5,	/* (0x71) */
	5,	/* (0x72) */
	5,	/* (0x73) */
	4,	/* (0x74) */
	5,	/* (0x75) */
	6,	/* (0x76) */
	6,	/* (0x77) */
	5,	/* (0x78) */
	5,	/* (0x79) */
	5,	/* (0x7a) */
	5,	/* (0x7b) */
	4,	/* (0x7c) */
	5,	/* (0x7d) */
	5,	/* (0x7e) */
};

static const FontDesc stellaDesc = {
  "04b-16b-10",                            /* font name */
  9,                                       /* max width in pixels */
  10,                                      /* height in pixels */
  8,                                       /* ascent (baseline) height */
  33,                                      /* first character in bitmap */
  94,                                      /* font size in glyphs */
  _stella_font_bits,                       /* 16-bit right-padded bitmap data */
  0,  /* no encode table*/                 /* offsets into bitmap data */
  _stella_sysfont_width,                   /* character widths or NULL if fixed */
  33,                                      /* default char (not glyph index) */
  sizeof(_stella_font_bits)/sizeof(uInt16) /* # words of bitmap_t bits */
};

} // namespace GUI

#endif
