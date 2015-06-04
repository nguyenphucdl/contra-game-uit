#include "Chapter6App.h"

Chapter6App::Chapter6App()
	: Framework::Game()
	//, m_testGameTask(Task::GAME_PRIORITY)
	, m_gameStateManager(Task::GAME_PRIORITY)
{
}

Chapter6App::~Chapter6App()
{
}

bool Chapter6App::Initialize()
{
	Log::info(Log::LOG_LEVEL_MIN, "[Chapter6App] Initialize... !\n");

	bool success = Framework::Game::Initialize();

	if(success)
	{
		//m_kernel.AddTask(&m_testGameTask);
		m_kernel.AddTask(&m_gameStateManager);
	}

	return success;
}