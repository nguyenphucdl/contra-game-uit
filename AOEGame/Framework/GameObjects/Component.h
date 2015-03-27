#ifndef __COMPONENT_H__
#define __COMPONENT_H__

namespace Framework
{
	class GameObject;

	class Component
	{
	private:
		GameObject*			m_pOwner;


	public:
		explicit Component(GameObject* pOwner)
			: m_pOwner(pOwner)
		{
		}

		virtual ~Component() { }

		virtual void Initialize() = 0;

		GameObject* GetOwner() { return m_pOwner; }
	};
}
#endif//__COMPONENT_H__