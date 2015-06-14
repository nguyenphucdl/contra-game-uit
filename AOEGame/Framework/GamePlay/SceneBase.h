#ifndef __SCENE_BASE_H__
#define __SCENE_BASE_H__

#include "../Application/Context.h"
#include "../GameState/GameState.h"

namespace Framework
{
	class SceneBase
		: public GameState
	{
	private:
		SceneStates	 m_sceneState;
	public:
		SceneBase();
		~SceneBase();

		SceneStates	GetScenceState() { return m_sceneState; }
		void		SetScenceState(SceneStates state) { m_sceneState = state; }

		virtual void Init() = 0;
		virtual void Update() = 0;
		virtual void Draw() = 0;
		virtual void Pause() = 0;
		virtual void Resume() = 0;

		virtual void Entered() = 0;
		virtual void Leaving() = 0;
		virtual void Obscuring() = 0;
		virtual void Revealed() = 0;
	};
}
#endif