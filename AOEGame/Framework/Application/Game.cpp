#include "Game.h"
#include "../Log/Log.h"
#include "../Utilities/FPSCounter.h"
namespace Framework
{
	Game::Game()
		: m_windowsTask(Task::PLATFORM_PRIORITY)
	{
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

		return ret;
	}

	bool Game::CreateMainWindow(HINSTANCE hInstance, int nCmdShow)
	{
		Log::info(Log::LOG_LEVEL_ROOT, "[Game][CreateMainWindow] entering...\n");
		return m_windowsTask.CreateMainWindow(hInstance, nCmdShow);
	}

	void Game::Run()
	{	
		FPSCounter::GetSingletonPtr()->StartCounter();
		

		m_kernel.Execute();


		Console::GetSingletonPtr()->print("Update time (%lf)", FPSCounter::GetSingletonPtr()->GetLastCounter());
		Console::GetSingletonPtr()->print("FPS (%lf)", ((double)1.0f) / FPSCounter::GetSingletonPtr()->GetLastCounter());
		Console::GetSingletonPtr()->print("Max time (%lf)", ((double)1.0f) / FPSCounter::GetSingletonPtr()->GetMinCounter());
		Console::GetSingletonPtr()->print("Min time (%lf)", ((double)1.0f) / FPSCounter::GetSingletonPtr()->GetMaxCounter());
		Console::GetSingletonPtr()->print("FPS Timer (%f)", 1.0f / Timer::GetSingletonPtr()->GetTimeSim());
		Console::GetSingletonPtr()->print("Timeer sim (%f)", Timer::GetSingletonPtr()->GetTimeSim());
		//}
		//Timer::GetSingletonPtr()->Update();
		//if (Timer::GetSingletonPtr()->GetTimeTotal() > 0.03333333f) // NEED REFACTOR
		//{
			//m_kernel.Execute();
			//Timer::GetSingletonPtr()->Reset();
		//}
		
		FPSCounter::GetSingletonPtr()->GetCounter();
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
		assert(EventManager::GetSingletonPtr());
		delete EventManager::GetSingletonPtr();
		assert(TextureManager::GetSingletonPtr());
		delete TextureManager::GetSingletonPtr();
		assert(Input::GetSingletonPtr());
		delete Input::GetSingletonPtr();
		assert(Window::GetSingletonPtr());
		delete Window::GetSingletonPtr();
		assert(Console::GetSingletonPtr());
		delete Console::GetSingletonPtr();
		assert(FPSCounter::GetSingletonPtr());
		delete FPSCounter::GetSingletonPtr();
		assert(CollisionManager::GetSingletonPtr());
		delete CollisionManager::GetSingletonPtr();
	}
}
