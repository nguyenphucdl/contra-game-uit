// Constants.h v1.0
#ifndef __CONSTANTS_H__			// prevent multiple definitions if this 
#define __CONSTANTS_H__			// ..file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>

//-----------------------------------------------
// Useful macros
//-----------------------------------------------
// Safely delete pointer referenced item
#define SAFE_DELETE(ptr) { if(ptr) { delete (ptr); (ptr)=NULL; } }
// Safely release pointer referenced item
#define SAFE_RELEASE(ptr) { if(ptr) { (ptr)->Release(); (ptr) = NULL; } }
// Safely delete pointer referenced array
#define SAFE_DELETE_ARRAY(ptr) { if(ptr) { delete [](ptr); (ptr)=NULL; } }
// transparent color (magenta)
// Color defines
#define COLOR_ARGB DWORD
#define SETCOLOR_ARGB(a,r,g,b) \
    ((COLOR_ARGB)((((a)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff)))
#define TRANSCOLOR  SETCOLOR_ARGB(0,255,0,255)  
//-----------------------------------------------
//                  Constants
//-----------------------------------------------
// window
const char CLASS_NAME[] = "Spacewar";
const char GAME_TITLE[] = "Game Engine Part 1";
const bool FULLSCREEN = false;              // windowed or fullscreen
const UINT GAME_WIDTH =  640;               // width of game in pixels
const UINT GAME_HEIGHT = 480;               // height of game in pixels

// game
const double PI = 3.14159265;
const float FRAME_RATE  = 200.0f;               // the target frame rate (frames/sec)
const float MIN_FRAME_RATE = 10.0f;             // the minimum frame rate
const float MIN_FRAME_TIME = 1.0f/FRAME_RATE;   // minimum desired time for 1 frame
const float MAX_FRAME_TIME = 1.0f/MIN_FRAME_RATE; // maximum time used in calculations

// key mappings
// In this game simple constants are used for key mappings. If variables were used
// it would be possible to save and restore key mappings from a data file.
const UCHAR ESC_KEY      = VK_ESCAPE;   // escape key
const UCHAR ALT_KEY      = VK_MENU;     // Alt key
const UCHAR ENTER_KEY    = VK_RETURN;   // Enter key


namespace ConfigKey
{
	const char GAME_WIDTH[] = "GAME_WIDTH";
	const char GAME_HEIGHT[] = "GAME_HEIGHT";
	const char FULLSCREEN[] = "FULLSCREEN";
	const char GAME_TITLE[] = "GAME_TITLE";
	const char CLASS_NAME[] = "CLASS_NAME";
}
/*LƯU Ý 
	const wchar_t *GAME_WIDTH2[] = L"GAME_WIDTH"; => ERROR already defined
*/

#define KEYBOARD_BUFFER_SIZE	1024


#endif