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
		ret = m_kernel.AddTask(AudioManager::GetSingletonPtr());
		
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

		FPSCounter::GetSingletonPtr()->StartTimeCounter(5);

		m_kernel.Execute();

		double updateTime = ((double)1.0f) / FPSCounter::GetSingletonPtr()->GetTimerCounter(5);
		double minUpdateTime = ((double)1.0f) / FPSCounter::GetSingletonPtr()->GetMaxTimeCounter(5);
		double maxUpdateTime = ((double)1.0f) / FPSCounter::GetSingletonPtr()->GetMinTimeCounter(5);
		Console::GetSingletonPtr()->print("Update time (%lf)", updateTime);
		Console::GetSingletonPtr()->print("Min Update time (%lf)", minUpdateTime);
		Console::GetSingletonPtr()->print("Max Update time (%lf)", maxUpdateTime);
		Console::GetSingletonPtr()->print("Render time (%lf)", Timer::GetSingletonPtr()->GetTimeEslapsed(TimerTypes::RenderCount));
		Console::GetSingletonPtr()->print("Timer sim (%f)", Timer::GetSingletonPtr()->GetTimeSim());
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
		new AudioManager(Task::AUDIO_PRIORITY);
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
