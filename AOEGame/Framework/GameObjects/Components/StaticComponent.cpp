#include "StaticComponent.h"
#include "../../Renderer/Renderer.h"
namespace Framework
{
	StaticComponent::StaticComponent(GameObject* pOwner)
		: Component(pOwner)
		, m_bound()
	{
	}

	StaticComponent::~StaticComponent()
	{
	}

	void StaticComponent::Initialize()
	{
		//Debug renderable
		m_renderable.IsVisible(false);
		m_renderable.SetZIndex(1000);
		TextureRegion* nullTexture = new TextureRegion(NULL, m_bound);
		m_renderable.SetTextureRegion(nullTexture);
		m_renderable.SetOrigin(Vector3(m_bound.left, m_bound.top, 1.0f));

		assert(Renderer::GetSingletonPtr());
		Renderer::GetSingleton().AddRenderable(&m_renderable);
	}
}