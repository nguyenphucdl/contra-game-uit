#include "SceneBase.h"

namespace Framework
{
	SceneBase::SceneBase()
		: GameState()
		, m_sceneState(SceneStates::Queue)
	{
		
	}

	SceneBase::~SceneBase()
	{
	}
}