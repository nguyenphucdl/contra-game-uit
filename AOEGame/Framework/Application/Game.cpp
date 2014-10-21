#include "Game.h"
#include "../Log/Log.h"


namespace Framework
{
	Game::Game()
		: m_windowsTask(Task::PLATFORM_PRIORITY)
	{
		CHAR NPath[MAX_PATH];
		GetCurrentDirectory(MAX_PATH, NPath);
		Log::info(Log::LOG_LEVEL_ROOT, "Root path is %s\n", NPath);
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
		//m_kernel.AddTask(TextureManager::GetSingletonPtr());
		// Add custom task
		
		return ret;
	}

	bool Game::CreateMainWindow(HINSTANCE hInstance, int nCmdShow)
	{
		Log::info(Log::LOG_LEVEL_ROOT, "[Game][CreateMainWindow] entering...\n");
		return m_windowsTask.CreateMainWindow(hInstance, nCmdShow);
	}

	void Game::Run()
	{	
		m_kernel.Execute();
	}

	void Game::DestroyAll()
	{
		m_windowsTask.DestroyMainWindow();
	}

	void Game::CreateSingletons()
	{
		// Create all task singleton
		new Timer(Task::TIMER_PRIORITY);
		new Renderer(Task::RENDER_PRIORITY);
		new TextureManager(Task::FILE_PRIORITY);
		new EventManager();
		new Input(Window::GetSingletonPtr()->GetWindowHandle(), Task::PLATFORM_PRIORITY);
	}

	void Game::DestroySingletons()
	{
		// Delete all task handle
		assert(Timer::GetSingletonPtr());
		delete Timer::GetSingletonPtr();
	}
}
