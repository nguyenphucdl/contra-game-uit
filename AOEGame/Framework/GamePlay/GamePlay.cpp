#include "GamePlay.h"
#include "TileMapScene.h"
#include "../Renderer/Renderer.h"
#include "../Collision/CollisionManager.h"
#include "../Renderer/Texture/TextureManager.h"
#include "../../CommonGameFactory.h"
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

		TileMapScene* scene1 = new TileMapScene();
		scene1->SetObjectFactory(m_objectFactory);
		scene1->LoadSceneFromFile("Resources\\Maps\\Scence1-Map1\\Scence1-Map1.tmx");
		
		TileMapScene* scene2 = new TileMapScene();
		scene2->SetObjectFactory(m_objectFactory);
		scene2->LoadSceneFromFile("Resources\\Maps\\Scence2-Map1\\Scence2-Map1.tmx");

		TileMapScene* scene3 = new TileMapScene();
		scene3->SetObjectFactory(m_objectFactory);
		scene3->LoadSceneFromFile("Resources\\Maps\\Scence3-Map1\\Scence3-Map1.tmx");

		TileMapScene* scene4 = new TileMapScene();
		scene4->SetObjectFactory(m_objectFactory);
		scene4->LoadSceneFromFile("Resources\\Maps\\Scence4-Map1\\Scence4-Map1.tmx");

		TileMapScene* scene5 = new TileMapScene();
		scene5->SetObjectFactory(m_objectFactory);
		scene5->LoadSceneFromFile("Resources\\Maps\\Scence5-Map1\\Scence5-Map1.tmx");
	
		TileMapScene* scene6 = new TileMapScene();
		scene6->SetObjectFactory(m_objectFactory);
		scene6->LoadSceneFromFile("Resources\\Maps\\Scence6-Map1\\Scence6-Map1.tmx");

		//for each and initlize scene
		
		//scene2->Init();
		//scene3->Init();
		//scene4->Init();
		//scene5->Init();
		//scene6->Init();
		//scene1->Init();

		// Add to queue
		m_sceneQueue.push(scene1);
		m_sceneQueue.push(scene2);
		m_sceneQueue.push(scene3);
		m_sceneQueue.push(scene4);
		m_sceneQueue.push(scene5);
		m_sceneQueue.push(scene6);
		m_current = m_sceneQueue.front();
		m_current->Init();
		//m_current->Entered();
		//Renderer::GetSingletonPtr()->GetCamera().ResetViewport();
	}

	void GamePlay::Update()
	{
		if (m_current->GetScenceState() == SceneStates::Completed)
		{
			//Renderer::GetSingletonPtr()->GetCamera().ResetViewport();
			m_popScenes.push(m_current);
			m_sceneQueue.pop();
			m_current = m_sceneQueue.front();
			m_current->Init();
		}
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