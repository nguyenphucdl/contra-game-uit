#define WIN32_LEAN_AND_MEAN

#include <windows.h>

#ifndef _USE_OLD_OSTREAMS
using namespace std;
#endif
#include <conio.h>	// for debug
#include <stdio.h>  // for debug
#include <crtdbg.h> // for detectubg momory leaks
#include "Framework\Debug\DebugConsole.h" // for output debug to cmd

#include "Framework\Application\Game.h" // include Main Application headers

using namespace Framework;


// Game pointers
Framework::Game *game = NULL;


//=============================================================================
// Starting point for a Windows application
// Parameters are:
//   hInstance - handle to the current instance of the application
//   hPrevInstance - always NULL, obsolete parameter, maintained for backwards compatibilty
//   lpCmdLine - pointer to null-terminated string of command line arguments
//   nCmdShow - specifies how the window is to be shown
//=============================================================================
int WINAPI WinMain( HINSTANCE hInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR     lpCmdLine,
                    int       nCmdShow)
{
	#ifdef _DEBUG
	RedirectIOToConsole();
	#endif

    MSG	 msg;

	// Create the game, sets up message handler
	game = new Framework::Game;
	GameConfig::LoadConfig();

    // Create the window
	if (!game->CreateMainWindow(hInstance, nCmdShow))
        return false;
	
	try
	{
		game->Initialize();  // throws GameError

		// main message loop
		int done = 0;
		while (!done)
		{
			if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				// look for quit message
				if(msg.message == WM_QUIT)
					done = 1;

				// decode and pass messages on to WinProc
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			} else {
				game->Run(); // run the game loop
			}
		}
		SAFE_DELETE(game);	// free memory before exit
		return msg.wParam;
	}
	catch(const GameError &err)
	{
		game->DestroyAll();
		MessageBox(NULL, err.getMessage(), "Error", MB_OK);

	}
	catch(...)
	{
		game->DestroyAll();
		MessageBox(NULL, "Unknown error occured in game.", "Error", MB_OK);
	}
    
	Sleep(2000);
    return msg.wParam;
}
//fprintf(stdout, "Test output to stdout\n");
