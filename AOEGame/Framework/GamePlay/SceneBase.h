#ifndef __SCENE_BASE_H__
#define __SCENE_BASE_H__

#include "../Application/Context.h"

namespace Framework
{
	class SceneBase
	{
	private:

	public:
		SceneBase();
		~SceneBase();

		virtual void Init() = 0;
		virtual void Update() = 0;
		virtual void Draw() = 0;
		virtual void Pause() = 0;
		virtual void Resume() = 0;
	};
}
#endif