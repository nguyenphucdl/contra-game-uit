#include "GamePlay.h"
#include "TileMapScene.h"
#include "../Collision/CollisionManager.h"
#include "../Renderer/Texture/TextureManager.h"
#include "../../ContraGameFactory.h"


namespace Framework
{
	GamePlay::GamePlay()
		: m_scenes()
	{
	}

	GamePlay::~GamePlay()
	{
	}

	void GamePlay::Load()
	{
		CollisionManager::GetSingletonPtr()->AddCollisionBin();

		m_pPlayerObject = ContraGameFactory::GetSingletonPtr()->GetPlayerObject();
		m_pCameraObject = ContraGameFactory::GetSingletonPtr()->GetCameraObject(m_pPlayerObject);

		m_tileMapScene = new TileMapScene();
		
		m_tileMapScene->LoadSceneFromFile("Resources\\Maps\\Scence1-Map1\\Scence1-Map1.tmx");
		m_tileMapScene->SetPlayerObject(m_pPlayerObject);
		m_tileMapScene->SetCameraObject(m_pCameraObject);
	}

	void GamePlay::Initialize()
	{
		//for each and initlize scene
		m_tileMapScene->Init();
	}

	void GamePlay::Entered()
	{
		m_tileMapScene->Update();
	}

	void GamePlay::Leaving()
	{

	}

	void GamePlay::Obscuring()
	{

	}

	void GamePlay::Revealed()
	{

	}
}