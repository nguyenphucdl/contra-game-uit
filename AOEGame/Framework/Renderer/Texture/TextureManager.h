#ifndef __TEXTURE_MANAGER__
#define	__TEXTURE_MANAGER__


#include "../../Kernel/Task.h"
#include "../../Renderer/Renderer.h"// Test
#include "Texture.h"	// TEMP ! 
//#include "../../Utilities/Timer.h" //Test
namespace Framework
{
	

	class TextureManager 
				: public Task
				, public Singleton<TextureManager>
	{
	private:
		typedef std::vector<Texture*>			TextureVector;
		typedef std::vector<Texture*>::iterator TextureVectorIterator;
		typedef std::vector<std::string>		TextureRegister;
		typedef	TextureRegister::iterator		TextureRegisterIterator;

		TextureVector				 m_textureVector;
		TextureRegister				 m_textureRegister;

	private:
		void		AddTexture(Texture *pTexture);
		void		RemoveTexture(Texture *pTexture);
	public:
		explicit TextureManager(const unsigned int priority);
		virtual ~TextureManager();

		void		Load();
		void		RegisterTexture(std::string filename);
		void		RegisterTexture(std::string filename, Texture* texture);
		void		UnRegisterTexture(std::string filename);
		void		Destroy();
		Texture*	GetTexture(std::string filename);
		void	LoadTexture(std::string filename);

	public:
		// From Task
		virtual	bool	Start();
		virtual	void	OnSuspend();
		virtual void	Update();
		virtual void	OnResume();
		virtual void	Stop();

		// Test
		friend void RegisterTexture(std::string filename);
		friend void TextureLoad();
		// Temp
		friend Texture*	GetTexture(std::string filename);
	};

	inline void RegisterTexture(std::string filename)
	{
		TextureManager::GetSingletonPtr()->RegisterTexture(filename);
	}

	inline void RegisterTexture(std::string filename, Texture* texture)
	{
		TextureManager::GetSingletonPtr()->RegisterTexture(filename, texture);
	}

	inline void TextureLoad()
	{
		TextureManager::GetSingletonPtr()->Load();
	}

	inline Texture* GetTexture(std::string filename)
	{
		return TextureManager::GetSingletonPtr()->GetTexture(filename);
	}
}

#endif//__TEXTURE_MANAGER__