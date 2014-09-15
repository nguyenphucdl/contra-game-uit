#include "Game.h"
#include "../Log/Log.h"


namespace Framework
{
	Game::Game()
		: m_windowsTask(Task::PLATFORM_PRIORITY)
	{
	}

	Game::~Game()
	{
	}

	bool Game::Initialize()
	{
		bool ret = true;

		CreateSingletons();

		m_kernel.AddTask(&m_windowsTask);
		m_kernel.AddTask(Timer::GetSingletonPtr());
		m_kernel.AddTask(Renderer::GetSingletonPtr());
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

	}

	void Game::DestroySingletons()
	{
		// Delete all task handle
		assert(Timer::GetSingletonPtr());
		delete Timer::GetSingletonPtr();
	}
}
