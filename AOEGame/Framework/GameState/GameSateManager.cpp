#include "GameStateManager.h"

namespace Framework
{
	GameStateManager::GameStateManager(const unsigned int priority)
		: Task(priority, "GamePlay1Task")
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
		m_currentGamePlay = new GamePlay();
		m_currentGamePlay->Load();
		m_currentGamePlay->Initialize();
		return true;
	}

	void GameStateManager::OnSuspend()
	{

	}

	void GameStateManager::Update()
	{
		//check state
		m_currentGamePlay->Entered();
		//if pass level
		//m_currentGamePlay->Leaving();
	}

	void GameStateManager::OnResume()
	{

	}

	void GameStateManager::Stop()
	{

	}
}