#include "GameStateManager.h"

namespace Framework
{
	GameStateManager::GameStateManager()
		: Task(Task::GAME_PRIORITY, "GamePlay1Task")
	{
	}

	GameStateManager::~GameStateManager()
	{
	}

	void GameStateManager::Switch(GameState* state)
	{

	}

	GameState* GameStateManager::Pop()
	{
		return nullptr;
	}

	void GameStateManager::Push(GameState* state)
	{

	}

	GameState* GameStateManager::Peek()
	{
		return nullptr;
	}

	bool GameStateManager::Start()
	{
		return true;
	}

	void GameStateManager::OnSuspend()
	{

	}

	void GameStateManager::Update()
	{

	}

	void GameStateManager::OnResume()
	{

	}

	void GameStateManager::Stop()
	{

	}
}