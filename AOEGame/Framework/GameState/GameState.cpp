#include "GameState.h"

namespace Framework
{
	GameState::GameState()
	{
		D3DXMatrixIdentity(&m_transitionMaxtrix);
	}

	GameState::~GameState()
	{
	}
}