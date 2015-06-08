#include "GameStateManager.h"
#include "../EventManager/EventManager.h"

namespace Framework
{
	GameStateManager::GameStateManager(const unsigned int priority)
		: Task(priority, "GamePlay1Task")
		, m_paused(false)
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
		Framework::AttachEvent(ExecutorIDs::SysInput, Events::SYS_PAUSE_RESUME_EVENT, *this);

		m_currentGamePlay = new GamePlay();
		m_currentGamePlay->Init();
		return true;
	}

	void GameStateManager::OnSuspend()
	{

	}

	void GameStateManager::Update()
	{
		if (!m_paused)
		{
			m_currentGamePlay->Update();
		}
		m_currentGamePlay->Draw();
	}

	void GameStateManager::OnResume()
	{

	}

	void GameStateManager::Stop()
	{

	}

	void GameStateManager::HandleEvent(Event* pEvent)
	{
		switch (pEvent->GetID())
		{
		case Events::SYS_PAUSE_RESUME_EVENT:
			m_paused = (bool)pEvent->GetData();
			break;
		default:
			break;
		}
	}
}