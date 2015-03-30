#include "Game.h"
#include "../Log/Log.h"


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
		//ret = m_kernel.AddTask(EventManager::GetSingletonPtr());
		ret = m_kernel.AddTask(Timer::GetSingletonPtr());
		ret = m_kernel.AddTask(Renderer::GetSingletonPtr());
		ret = m_kernel.AddTask(Input::GetSingletonPtr());
		
		
		return ret;
	}

	bool Game::CreateMainWindow(HINSTANCE hInstance, int nCmdShow)
	{
		Log::info(Log::LOG_LEVEL_ROOT, "[Game][CreateMainWindow] entering...\n");
		return m_windowsTask.CreateMainWindow(hInstance, nCmdShow);
	}

	void Game::Run()
	{	
		if (Timer::GetSingletonPtr()->GetTimeTotal() > 0.0333f) // NEED REFACTOR
		{
			m_kernel.Execute();
			Timer::GetSingletonPtr()->Reset();
		}
		else
		{
			Timer::GetSingletonPtr()->Update();
		}
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
	}

	void Game::DestroySingletons()
	{
		// Delete all task handle
		assert(Timer::GetSingletonPtr());
		delete Timer::GetSingletonPtr();
	}
}
