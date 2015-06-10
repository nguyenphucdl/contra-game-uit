#include "GamePlay.h"
#include "TileMapScene.h"
#include "../Renderer/Renderer.h"
#include "../Collision/CollisionManager.h"
#include "../Renderer/Texture/TextureManager.h"
#include "../../ContraGameFactory.h"
#include "../Utilities/FPSCounter.h"
#include "../Utilities/Console.h"

namespace Framework
{
	GamePlay::GamePlay()
		: m_scenes()
	{
	}

	GamePlay::~GamePlay()
	{
	}

	void GamePlay::Init()
	{
		m_pPlayerObject = ContraGameFactory::GetSingletonPtr()->GetPlayerObject();
		m_pCameraObject = ContraGameFactory::GetSingletonPtr()->GetCameraObject(m_pPlayerObject);

		m_tileMapScene = new TileMapScene();

		m_tileMapScene->LoadSceneFromFile("Resources\\Maps\\Scence1-Map1\\Scence1-Map1.tmx");
		m_tileMapScene->SetPlayerObject(m_pPlayerObject);
		m_tileMapScene->SetCameraObject(m_pCameraObject);


		m_scene2 = new TileMapScene();
		m_scene2->LoadSceneFromFile("Resources\\Maps\\Scence2-Map1\\Scence2-Map1.tmx");
		m_scene2->SetPlayerObject(m_pPlayerObject);
		m_scene2->SetCameraObject(m_pCameraObject);

		//for each and initlize scene
		m_tileMapScene->Init();

		//m_scene2->Init();
	}

	void GamePlay::Update()
	{
		//m_current Scene
		m_tileMapScene->Update();

		//m_scene2->Update();
	}

	void GamePlay::Draw()
	{
		/*IMPORTANT*/
		Renderer::GetSingletonPtr()->ClearRenderables();
		
		
		m_tileMapScene->Draw();

		//m_scene2->Draw();

		
	}

	void GamePlay::Pause()
	{

	}

	void GamePlay::Resume()
	{

	}

	void GamePlay::Entered()
	{

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