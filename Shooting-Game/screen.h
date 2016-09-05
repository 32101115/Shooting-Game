/*
 * Exported with nin10kit v1.1
 * Invocation command was nin10kit -mode4 screen GameEnd.jpg GameWin.jpg titlescreen.jpg 
 * Time-stamp: Monday 11/09/2015, 14:27:25
 * 
 * Image Information
 * -----------------
 * GameEnd.jpg 240@160
 * GameWin.jpg 240@160
 * titlescreen.jpg 302@198
 * 
 * Quote/Fortune of the Day!
 * -------------------------
 * 
 * All bug reports / feature requests are to be sent to Brandon (bwhitehead0308@gmail.com)
 */

#ifndef SCREEN_H
#define SCREEN_H

extern const unsigned short screen_palette[255];
#define SCREEN_PALETTE_SIZE 255

extern const unsigned short GameEnd[19200];
#define GAMEEND_SIZE 19200
#define GAMEEND_WIDTH 240
#define GAMEEND_HEIGHT 160

extern const unsigned short GameWin[19200];
#define GAMEWIN_SIZE 19200
#define GAMEWIN_WIDTH 240
#define GAMEWIN_HEIGHT 160

extern const unsigned short titlescreen[29898];
#define TITLESCREEN_SIZE 29898
#define TITLESCREEN_WIDTH 302
#define TITLESCREEN_HEIGHT 198

#endif

