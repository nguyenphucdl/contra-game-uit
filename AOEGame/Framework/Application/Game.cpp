#include "Game.h"
#include "../Log/Log.h"
#include "../Utilities/FPSCounter.h"
namespace Framework
{
	Game::Game()
		: m_windowsTask(Task::PLATFORM_PRIORITY)
	{
		//CHAR NPath[MAX_PATH];
		//GetCurrentDirectory(MAX_PATH, NPath);
		//Log::info(Log::LOG_LEVEL_ROOT, "Root path is %s\n", NPath);
		Log::start();
	}

	Game::~Game()
	{
	}

	bool Game::Initialize()
	{
		bool ret = true;

		CreateSingletons();

		ret = m_kernel.AddTask(&m_windowsTask);
		ret = m_kernel.AddTask(Timer::GetSingletonPtr());
		ret = m_kernel.AddTask(Renderer::GetSingletonPtr());
		ret = m_kernel.AddTask(Input::GetSingletonPtr());
		
		Console::GetSingletonPtr()->init();

		/*REGISTER EVENT*/
		
		//RegisterEvent(ExecutorIDs::SysRender, Events::SYS_PRE_RENDER_EVENT);
		//RegisterEvent(ExecutorIDs::SysRender, Events::SYS_RENDER_EVENT);
		//RegisterEvent(ExecutorIDs::SysRender, Events::SYS_POST_RENDER_EVENT);
		
		
		return ret;
	}

	bool Game::CreateMainWindow(HINSTANCE hInstance, int nCmdShow)
	{
		Log::info(Log::LOG_LEVEL_ROOT, "[Game][CreateMainWindow] entering...\n");
		return m_windowsTask.CreateMainWindow(hInstance, nCmdShow);
	}

	void Game::Run()
	{	
		DWORD tick_per_frame = 100 / 60;
		__int64 frame_start = GetTickCount64();


		FPSCounter::GetSingletonPtr()->StartCounter();
		
		
		__int64 now = GetTickCount64();
		__int64 delta = now - frame_start;

		//if (delta >= tick_per_frame)
		//{
			//Console::GetSingletonPtr()->print("Update time (%i)", delta);
			//frame_start = now;
			m_kernel.Execute();
			Console::GetSingletonPtr()->print("Update time (%lf)", FPSCounter::GetSingletonPtr()->GetLastCounter());
			Console::GetSingletonPtr()->print("FPS (%lf)", ((double)1.0f) / FPSCounter::GetSingletonPtr()->GetLastCounter());
			Console::GetSingletonPtr()->print("Max time (%lf)", ((double)1.0f) / FPSCounter::GetSingletonPtr()->GetMinCounter());
			Console::GetSingletonPtr()->print("Min time (%lf)", ((double)1.0f) / FPSCounter::GetSingletonPtr()->GetMaxCounter());
		//}
		//Timer::GetSingletonPtr()->Update();
		//if (Timer::GetSingletonPtr()->GetTimeTotal() > 0.03333333f) // NEED REFACTOR
		//{
			//m_kernel.Execute();
			//Timer::GetSingletonPtr()->Reset();
		//}
		
		FPSCounter::GetSingletonPtr()->GetCounter();
		
		//Console::GetSingletonPtr()->print("Update time (%i)", counter);
		
		
	}

	void Game::DestroyAll()
	{
		m_windowsTask.DestroyMainWindow();
	}

	void Game::CreateSingletons()
	{
		// Create all task singleton
		new EventManager();
		new Timer(Task::TIMER_PRIORITY);
		new Renderer(Task::RENDER_PRIORITY);
		new TextureManager(Task::FILE_PRIORITY);
		new Input(Window::GetSingletonPtr()->GetWindowHandle(), Task::PLATFORM_PRIORITY);
		new CollisionManager();
		new Console();
		new FPSCounter();
	}

	void Game::DestroySingletons()
	{
		// Delete all task handle
		assert(Timer::GetSingletonPtr());
		delete Timer::GetSingletonPtr();
	}
}
