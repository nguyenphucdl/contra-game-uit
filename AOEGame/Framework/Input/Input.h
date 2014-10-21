#ifndef __INPUT_H__
#define __INPUT_H__

#include "../Application/Context.h"
#include "../Kernel/Task.h"
#include "../EventManager/EventManager.h"

namespace Framework
{
	class Input
		: public Task
		, public Singleton<Input>
	{
	private:
		HWND					m_hwnd;
		IDirectInput8*			m_di;
		HRESULT					m_result;

		// Keyboard
		IDirectInputDevice8*	m_keyboard;
		char					m_keyState[256];					// DirectInput keyboard state buffer 
		DIDEVICEOBJECTDATA		m_keyEvents[KEYBOARD_BUFFER_SIZE];	// Buffered keyboard data


		// Mouse
		IDirectInputDevice8*	m_mouse;
		DIMOUSESTATE			m_mouseState;
		POINT					m_mousePosition;

	private:
		void	_InitInputDevice();
		void	_InitKeyboard();
		void	_InitMouse();

	public:
		Input(HWND hwnd, const unsigned int priority);
		virtual ~Input();

		int		IsKeyDown(int keycode);

		// Task
		virtual bool Start();
		virtual void OnSuspend();
		virtual void Update();
		virtual void OnResume();
		virtual void Stop();
		
	};
}

#endif//__INPUT_H__