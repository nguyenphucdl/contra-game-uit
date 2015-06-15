#include "GamePlay.h"
#include "TileMapScene.h"
#include "../Renderer/Renderer.h"
#include "../Collision/CollisionManager.h"
#include "../Renderer/Texture/TextureManager.h"
#include "../../ContraGameFactory.h"
#include "../Utilities/FPSCounter.h"
#include "../Utilities/Console.h"
#include "../../MegamanMap1Factory.h"

namespace Framework
{
	GamePlay::GamePlay()
		: m_sceneQueue()
		, m_popScenes()
	{
	}

	GamePlay::~GamePlay()
	{
	}

	void GamePlay::Init()
	{
		m_objectFactory = new MegamanMap1Factory();

		GameObject*	playerScene1 = ContraGameFactory::GetSingletonPtr()->GetPlayerObject();
		GameObject* cameraScene1 = ContraGameFactory::GetSingletonPtr()->GetCameraObject(playerScene1);
		//GameObject* npcObjScene1 = ContraGameFactory::GetSingletonPtr()->GetNpcTestObject();
		TileMapScene* m_tileMapScene = new TileMapScene();
		m_tileMapScene->SetObjectFactory(m_objectFactory);
		m_tileMapScene->LoadSceneFromFile("Resources\\Maps\\Scence1-Map1\\Scence1-Map1.tmx");
		m_tileMapScene->SetCameraObject(cameraScene1);
		m_tileMapScene->AddUpdateObject(playerScene1);
		//m_tileMapScene->AddUpdateObject(npcObjScene1);
		

		GameObject*	playerScene2 = ContraGameFactory::GetSingletonPtr()->GetPlayerObject();
		GameObject* cameraScence2 = ContraGameFactory::GetSingletonPtr()->GetCameraObject(playerScene2);
		GameObject* npcObjScene2 = ContraGameFactory::GetSingletonPtr()->GetNpcTestObject();
		TileMapScene* m_scene2 = new TileMapScene();
		m_scene2->SetObjectFactory(m_objectFactory);
		m_scene2->LoadSceneFromFile("Resources\\Maps\\Scence2-Map1\\Scence2-Map1.tmx");
		m_scene2->SetCameraObject(cameraScence2);
		m_scene2->AddUpdateObject(playerScene2);
		m_scene2->AddUpdateObject(npcObjScene2);

		//for each and initlize scene
		m_tileMapScene->Init();
		m_scene2->Init();

		// Add to queue
		m_sceneQueue.push(m_tileMapScene);
		m_sceneQueue.push(m_scene2);
		m_current = m_sceneQueue.front();
	}

	void GamePlay::Update()
	{
		if (m_current->GetScenceState() == SceneStates::Completed)
		{
			m_popScenes.push(m_current);
			m_sceneQueue.pop();
		}
		m_current = m_sceneQueue.front();
		m_current->Update();
	}

	void GamePlay::Draw()
	{
		/*IMPORTANT*/
		Renderer::GetSingletonPtr()->ClearRenderables();
		
		m_current->Draw();
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