#include "TextureManager.h"


namespace Framework
{
	TextureManager::TextureManager(const unsigned int priority)
		: Task(priority, "TextureManager Task")
	{
		m_textureVector.reserve(10);//TEMP
		m_textureRegister.reserve(10);//TEMP
	}
	TextureManager::~TextureManager()
	{
	}
	void TextureManager::AddTexture(Texture *pTexture)
	{
		assert(pTexture);
		// if TextureManager initialized = true
		
		for(TextureVectorIterator iter = m_textureVector.begin(); iter != m_textureVector.end(); iter++)
		{
			Texture* pCurrent = *iter;
			if(pCurrent->GetName().compare(pTexture->GetName()) == 0)	// Already exist!
				return;
		}

		m_textureVector.push_back(pTexture);
	}
	void TextureManager::RemoveTexture(Texture *pTexture)
	{
		assert(pTexture);
		// if TextureManager initialized = true
		
		for(TextureVectorIterator iter = m_textureVector.begin(); iter != m_textureVector.end(); iter++)
		{
			Texture* pCurrent = *iter;
			if(pCurrent->GetName().compare(pTexture->GetName()) == 0)	// Already exist!
			{
				m_textureVector.erase(iter);
			}
		}
	}
	void TextureManager::Load()
	{
		// Execute load all textures
		for(TextureRegisterIterator iter = m_textureRegister.begin(); iter != m_textureRegister.end(); iter++)
		{
			LoadTexture(*iter);
		}
	}
	void TextureManager::Destroy()
	{
		m_textureRegister.clear();
		for(TextureVectorIterator iter = m_textureVector.begin(); iter != m_textureVector.end(); iter++)
		{
			Texture* pCurrent = *iter;
			pCurrent->Destroy();	
		}
		m_textureVector.clear();
	}
	void TextureManager::RegisterTexture(std::string filename)
	{
		for(TextureRegisterIterator iter = m_textureRegister.begin(); iter != m_textureRegister.end(); iter++)
		{
			if((*iter).compare(filename) == 0) // Already exist!
			{
				//Trace log
				return;
			}
		}
		m_textureRegister.push_back(filename);
		LoadTexture(filename);
	}
	void TextureManager::RegisterTexture(std::string filename, Texture* texture)
	{
		for (TextureRegisterIterator iter = m_textureRegister.begin(); iter != m_textureRegister.end(); iter++)
		{
			if ((*iter).compare(filename) == 0) // Already exist!
			{
				//Trace log
				return;
			}
		}
		AddTexture(texture);
	}
	void TextureManager::UnRegisterTexture(std::string filename)
	{
		for(TextureRegisterIterator iter = m_textureRegister.begin(); iter != m_textureRegister.end(); iter++)
		{
			if((*iter).compare(filename) == 0) // Already exist!
			{
				m_textureRegister.erase(iter);
			}
		}
	}
	Texture* TextureManager::GetTexture(std::string filename)
	{
		for(TextureVectorIterator iter = m_textureVector.begin(); iter != m_textureVector.end(); iter++)
		{
			Texture* pCurrent = *iter;
			if(pCurrent->GetName().compare(filename) == 0)	// Already exist!
			{
				return pCurrent;
			}
			//Trace log
			
		}
		return NULL;
	}
	void TextureManager::LoadTexture(std::string filename)
	{
		D3DXIMAGE_INFO		_info;
		HRESULT				_result = E_FAIL;
		LPDIRECT3DTEXTURE9	_texture = NULL;

		try
		{
			if(filename.c_str() == NULL)
				return;

			// Get width and height from file
			_result = D3DXGetImageInfoFromFile(filename.c_str(), &_info);
			if(FAILED(_result))
				return;

			// Create the new texture by loading from file
			_result = D3DXCreateTextureFromFileEx(
						Renderer::GetSingletonPtr()->getD3device(),
						filename.c_str(),
						_info.Width,
						_info.Height,
						1,
						0,
						D3DFMT_UNKNOWN,
						D3DPOOL_DEFAULT,
						D3DX_DEFAULT,
						D3DX_DEFAULT,
						TRANSCOLOR,
						&_info,
						NULL,
						&_texture);
			if(FAILED(_result))
				return;

			// Create new texture and add to list
			Texture* texture = new Texture(filename, _texture, _info);
			this->AddTexture(texture);
		}
		catch(...)
		{
			// Trace log
			throw(GameError(GameErrorNS::FATAL_ERROR, "Error in Graphics::loadTexture"));
		}
	}

	// From Task
	bool TextureManager::Start(){

		TextureManager::GetSingletonPtr()->RegisterTexture("mariobig.png");
		//TextureManager::GetSingletonPtr()->RegisterTexture("mariobigbigbullet.png");
		//TextureManager::GetSingletonPtr()->RegisterTexture("mariobigbullet.png");

		//TextureManager::GetSingletonPtr()->Load();

		/*HRESULT _result = D3DXCreateSprite(Renderer::GetSingletonPtr()->getD3device(), &m_spriteHandler);
		if(FAILED(_result))
			return false;*/
		//srect.left = 0; 
		//srect.top = 0; 
		

		return true;
	}
	void TextureManager::OnSuspend()
	{
	}
	void TextureManager::Update()
	{
		
		//if(SUCCEEDED(Renderer::GetSingletonPtr()->beginScene()))
		//{
		//	// render custom task
		//	//Log::info(Log::LOG_LEVEL_ROOT, "[Renderer] Updating... !\n");

		//	//this->DrawAll();

		//	//stop rendering
		//	Renderer::GetSingletonPtr()->endScene();
		//}
		//
		//Renderer::GetSingletonPtr()->handleLostGraphicsDevice();
		//

		//Renderer::GetSingletonPtr()->showBackBuffer();
	}
	void TextureManager::OnResume()
	{
	}
	void TextureManager::Stop()
	{
	}

	void TextureManager::DrawAll()
	{
		


		//Log::info(Log::LOG_LEVEL_ROOT, "[TextureManager] Updating... !\n");
		/* initialize random seed: */
		///srand (time(NULL));

		//m_spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
		
		//D3DXMATRIX matRotate;
		//D3DXMatrixIdentity(&matRotate);
		//D3DXVECTOR3 position(50, 100, 0);
		//D3DXVECTOR2 pos_center(250, 250);
		//D3DXMatrixTransformation2D(
		//&matRotate,
		//&pos_center,
		//0.0f,
		//&D3DXVECTOR2(1.0f, -1.0f),
		//NULL,
		//D3DXToRadian(0.0f),
		//&D3DXVECTOR2(position.x, position.y));

		//D3DXMATRIXA16 matWorld, matTranslate, matScale, rotate1;
		//D3DXMatrixIdentity(&matScale);
		//D3DXMatrixScaling( &matScale, 1.0f, -1.0f, 1.0f );

		//D3DXMatrixIdentity(&matTranslate);
		//D3DXMatrixTranslation( &matTranslate, -10, 600, 0 );
		////matWorld = matScale * matTranslate;
		//D3DXMatrixIdentity(&matWorld);
		//D3DXMatrixMultiply(&matWorld, &matScale, &matTranslate);
		//D3DXMatrixMultiply(&matWorld, &matRotate, &matWorld);

		////D3DXMatrixTranslation(&matWorld, -cameraX, cameraY, 0);

		//m_spriteHandler->SetTransform(&matWorld);
		//D3DXVECTOR3 position(0, 0, 0);

		/*Texture* pCurrent = GetTexture("mariobig.png");*/
		//RECT srect;
		/*srect.right = srect.left + pCurrent->GetWidth() /5;
		srect.bottom = srect.top + pCurrent->GetHeight() /2;
		

		m_spriteHandler->Draw(pCurrent->GetTexture(), &srect, NULL, &position, D3DCOLOR_XRGB(255,255,255));

		if(Timer::GetSingletonPtr()->GetTimeTotal() > MIN_FRAME_RATE / 100.0f)
		{
			Timer::GetSingletonPtr()->Reset();
			srect.left += pCurrent->GetWidth() /5;
		}*/
		
		

		//if(srect.left > pCurrent->GetWidth())
		//	srect.left = 0;
		/*for(TextureVectorIterator iter = m_textureVector.begin(); iter != m_textureVector.end(); iter++)
		{
			Texture* pCurrent = *iter;
			
			
			m_spriteHandler->Draw(pCurrent->GetTexture(), &srect, NULL, &position, D3DCOLOR_XRGB(255,255,255));
			position.x += 150;
			position.y += 150;
		}*/

		//D3DXMATRIX matDefaut;
		//D3DXMatrixInverse(&matDefaut,NULL, &matWorld);
		////D3DXMatrixTransformation2D(&matDefaut,NULL,0.0f,NULL,NULL,0.0f,NULL); 
		//m_spriteHandler->SetTransform(&matDefaut);

		/*m_spriteHandler->End();*/
	}
}