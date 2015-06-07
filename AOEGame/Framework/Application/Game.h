#ifndef __APPLICATION_H__                 // prevent multiple definitions if this 
#define __APPLICATION_H__                 // ..file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "../Platform/Window.h"
#include "../Kernel/Kernel.h"
#include "../Renderer/Renderer.h"
#include "../Utilities/Timer.h"
#include "../Utilities/GameConfig.h"
#include "../Renderer/Texture/TextureManager.h"
#include "../EventManager/EventManager.h"
#include "../Collision/CollisionManager.h"
#include "../Input/Input.h"
#include "../Utilities/Console.h"

namespace Framework
{
	class Game
	{
	protected:
		Kernel		m_kernel;
		Window		m_windowsTask;


		virtual void CreateSingletons();
		virtual void DestroySingletons();
		


	public:
		explicit Game();
		virtual ~Game();

		virtual bool Initialize();
		virtual void Run();
		virtual void DestroyAll();
		virtual bool CreateMainWindow(HINSTANCE hInstance, int nCmdShow);
	};
}
#endif //__APPLICATION_H__