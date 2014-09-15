#ifndef __WINDOW_H__
#define __WINDOW_H__

#include "../Kernel/Task.h"

namespace Framework
{
	class Window : public Task, public Singleton<Window>
	{
	private:
		static bool		m_bClosing;
	public:
		HWND		m_hwnd;		// Hande to window
		

	public:
		Window(const unsigned int priority);
		virtual ~Window();
		virtual bool CreateMainWindow(HINSTANCE hInstance, int nCmdShow);
		virtual void DestroyMainWindow();

		virtual bool	Start();
		virtual void	OnSuspend();
		virtual void	Update();
		virtual void	OnResume();
		virtual void	Stop();
		HWND			GetWindowHandle()		{ return m_hwnd; }

		static void		ClearClosing()			{ m_bClosing = false; }
		static bool		IsClosing()				{ return m_bClosing; }

		static LRESULT WINAPI WinProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam );
	};
}
#endif //__WINDOW_H__ 