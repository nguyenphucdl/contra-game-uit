#include "Input.h"

namespace Framework
{
	Input::Input(HWND hwnd, const unsigned int priority)
		: Task(priority, "Input Task")
		, m_hwnd(hwnd)
	{
	}

	Input::~Input()
	{
		if(m_keyboard != NULL)
		{
			m_keyboard->Unacquire();
			m_keyboard->Release();
		}
		if(m_mouse != NULL)
		{
			m_keyboard->Unacquire();
			m_keyboard->Release();
		}
		SAFE_RELEASE(m_di);
	}

	void Input::_InitInputDevice()
	{
		assert(m_hwnd);
		// Create Direct Input
		m_result = DirectInput8Create(
			GetModuleHandle(NULL),
			DIRECTINPUT_VERSION,
			IID_IDirectInput8,
			(void**)&m_di,
			NULL);

		if(FAILED(m_result))
			throw new GameError(GameErrorNS::FATAL_ERROR, "Unable to create Direct Input Object!");

		_InitKeyboard();
		_InitMouse();
	}

	void Input::_InitKeyboard()
	{
		// Create Keyboard 
		m_result = m_di->CreateDevice(GUID_SysKeyboard, &m_keyboard, NULL);

		if(FAILED(m_result))
			throw new GameError(GameErrorNS::FATAL_ERROR, "Unable to create Keyboard!");

		// Set the data format to "keyboard format" - a predefined data format 
		//
		// A data format specifies which controls on a device we
		// are interested in, and how they should be reported.
		//
		// This tells DirectInput that we will be passing an array
		// of 256 bytes to IDirectInputDevice::GetDeviceState.

		m_result = m_keyboard->SetDataFormat(&c_dfDIKeyboard);

		m_result = m_keyboard->SetCooperativeLevel(m_hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

		// IMPORTANT STEP TO USE BUFFERED DEVICE DATA!
		//
		// DirectInput uses unbuffered I/O (buffer size = 0) by default.
		// If you want to read buffered data, you need to set a nonzero
		// buffer size.
		//
		// Set the buffer size to DINPUT_BUFFERSIZE (defined above) elements.
		//
		// The buffer size is a DWORD property associated with the device.

		DIPROPDWORD dipdw;

		dipdw.diph.dwSize			= sizeof(DIPROPDWORD);
		dipdw.diph.dwHeaderSize		= sizeof(DIPROPHEADER);
		dipdw.diph.dwObj			= 0;
		dipdw.diph.dwHow			= DIPH_DEVICE;
		dipdw.dwData				= KEYBOARD_BUFFER_SIZE; // Arbitary buffer size

		m_result = m_keyboard->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);

		if(FAILED(m_result))
			throw new GameError(GameErrorNS::FATAL_ERROR, "Unable to set keyboard buffersize!");

		m_result = m_keyboard->Acquire();

		if(FAILED(m_result))
			throw new GameError(GameErrorNS::FATAL_ERROR, "Unable to set acquire keyboard!");

		Log::info(Log::LOG_LEVEL_ROOT, "[Input] Init keyboard successfully !\n");
	}

	void Input::_InitMouse()
	{
	}

	int Input::IsKeyDown(int keycode)
	{
		return (m_keyState[keycode] & 0x80) > 0;
	}

	// Task
	bool Input::Start()
	{
		_InitInputDevice();
		return true;
	}

	void Input::OnSuspend()
	{
	}

	void Input::Update()
	{
		/*LARGE_INTEGER timeStart;
		LARGE_INTEGER timeEnd;
		LARGE_INTEGER timeFreq;
		if (QueryPerformanceFrequency(&timeFreq) == false)
			throw(GameError(GameErrorNS::FATAL_ERROR, "Error initializing high resolution timer"));
		QueryPerformanceCounter(&timeStart);*/


		// Collect all key states first
		m_keyboard->GetDeviceState(sizeof(m_keyState), m_keyState);

		if(IsKeyDown(DIK_ESCAPE))
		{
			PostMessage(m_hwnd, WM_QUIT, 0, 0);
		}

		// Collect all buffered events
		DWORD dwElements = KEYBOARD_BUFFER_SIZE;
		m_result = m_keyboard->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), m_keyEvents, &dwElements, 0);
		
		if (SUCCEEDED(m_result))
		{
			if (m_result == DI_BUFFEROVERFLOW)
			{
				throw new GameError(GameErrorNS::FATAL_ERROR, "Buffer overflow!");
			}
			// Scan through all data, check if the key is pressed or released
			for (DWORD i = 0; i <dwElements; i++)
			{
				int keyCode = m_keyEvents[i].dwOfs;
				int keystate = m_keyEvents[i].dwData;
				/*if(keyCode < 0)
				continue;*/
				if ((keystate & 0x80) > 0)
				{
					//Sent KEYDOWN_EVENT with keycode parameters
					SendEvent(Events::KEY_DOWN_EVENT, (void *)keyCode);
					if (keyCode == DIK_SPACE)
					{
						SendEvent(Events::PLAYER_JUMP_EVENT);
					}
				}
				else
				{
					//Sent KEYDUP_EVENT with keycode parameters
					SendEvent(Events::KEY_UP_EVENT, (void*)keyCode);
				}
			}

		}
		else
		{
			// Switch to another application, cannot retrieve input device
			// Log::info(Log::LOG_LEVEL_HIGHT, "Cannot get device data!\n");
			Sleep(100);
			m_result = m_keyboard->Acquire();
			if (SUCCEEDED(m_result))
			{
				Log::info(Log::LOG_LEVEL_HIGHT, "Accquire input device successfully!\n");
			}
		}

		//QueryPerformanceCounter(&timeEnd);
		//LARGE_INTEGER numCounts = timeEnd.QuadPart � timeStart.QuadPart;
		//float frameDt = (float)((timeEnd.QuadPart - timeStart.QuadPart)) / (float)(timeFreq.QuadPart);
		//int k = 123;
	}

	void Input::OnResume()
	{
	}

	void Input::Stop()
	{
	}

}