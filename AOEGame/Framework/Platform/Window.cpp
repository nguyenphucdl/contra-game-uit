#include "Window.h"
#include <cassert>


namespace Framework
{
	bool Window::m_bClosing	= false;

	Window::Window(unsigned int priority) 
		:	Task(priority, "Window Task")
	{
		Log::info(Log::LOG_LEVEL_ROOT, "[Window] Constructor !\n");
	}

	//=============================================================================
	// Create the window
	// Returns: false on error
	//=============================================================================
	bool Window::CreateMainWindow(HINSTANCE hInstance, int nCmdShow)
	{
		Log::info(Log::LOG_LEVEL_ROOT, "[Window][CreateMainWindow] Running...!\n");
		WNDCLASSEX wcx; 
		HWND hwnd;
		std::string className = GameConfig::GetSingletonPtr()->Get(ConfigKey::CLASS_NAME);
		std::string gameTitle = GameConfig::GetSingletonPtr()->Get(ConfigKey::GAME_TITLE);
		int			gameWidth = GameConfig::GetSingletonPtr()->GetInt(ConfigKey::GAME_WIDTH);
		int			gameHeight = GameConfig::GetSingletonPtr()->GetInt(ConfigKey::GAME_HEIGHT);
 
		// Fill in the window class structure with parameters 
		// that describe the main window. 
		wcx.cbSize = sizeof(wcx);					// size of structure 
		wcx.style = CS_HREDRAW | CS_VREDRAW;		// redraw if size changes 
		wcx.lpfnWndProc = Window::WinProc;          // points to window procedure 
		wcx.cbClsExtra = 0;							// no extra class memory 
		wcx.cbWndExtra = 0;							// no extra window memory 
		wcx.hInstance = hInstance;					// handle to instance 
		wcx.hIcon = NULL; 
		wcx.hCursor = LoadCursor(NULL,IDC_ARROW);   // predefined arrow 
		wcx.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);    // black background brush 
		wcx.lpszMenuName =  NULL;					// name of menu resource 
		wcx.lpszClassName = className.c_str();		// name of window class 
		wcx.hIconSm = NULL;							// small class icon 
 
		// Register the window class. 
		// RegisterClassEx returns 0 on error.
		if (RegisterClassEx(&wcx) == 0)    // if error
			return false;

		// Create window
		hwnd = CreateWindow(
			className.c_str(),						// name of the window class
			gameTitle.c_str(),						// title bar text
			WS_OVERLAPPEDWINDOW,					// window style
			CW_USEDEFAULT,							// default horizontal position of window
			CW_USEDEFAULT,							// default vertical position of window
			gameWidth,								// width of window
			gameHeight,								// height of the window
			(HWND) NULL,							// no parent window
			(HMENU) NULL,							// no menu
			hInstance,								// handle to application instance
			(LPVOID) NULL);							// no window parameters

		// if there was an error creating the window
		if (!hwnd)
			return false;

		// Show the window
		ShowWindow(hwnd, nCmdShow);

		// Send a WM_PAINT message to the window procedure
		UpdateWindow(hwnd);

		//m_hwnd = hwnd;
		Window::m_hwnd = hwnd;

		return true;
	}

	//=============================================================================
	// window event callback function
	//=============================================================================
	LRESULT WINAPI Window::WinProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )
	{
		switch( msg )
		{
			case WM_DESTROY:
				//tell Windows to kill this program
				PostQuitMessage(0);
				return 0;
		}
		return DefWindowProc( hwnd, msg, wParam, lParam );
	}

	void Window::DestroyMainWindow()
	{
		Log::info(Log::LOG_LEVEL_ROOT, "[Window] DestroyMainWindow !\n");
		DestroyWindow(m_hwnd);
	}


	Window::~Window()
	{
	}

	bool Window::Start()
	{
		return true;
	}

	void Window::OnSuspend()
	{
	}

	void Window::Update()
	{
	}

	void Window::OnResume()
	{
	}

	void Window::Stop()
	{
	}
}