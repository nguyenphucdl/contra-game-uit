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
	bool TextureManager::Start()
	{	
		return true;
	}
	void TextureManager::OnSuspend()
	{
	}
	void TextureManager::Update()
	{
		
	}
	void TextureManager::OnResume()
	{
	}
	void TextureManager::Stop()
	{
	}
}