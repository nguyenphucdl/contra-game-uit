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
		m_renderable.IsVisible(true);
		m_renderable.SetUseBounds(true);
		m_renderable.SetBoundMin(Vector3(m_bound.left, m_bound.top, 1.0f));
		m_renderable.SetBoundMax(Vector3(m_bound.right, m_bound.bottom, 1.0f));
		m_renderable.SetZIndex(1000);
		m_renderable.SetDebug(true);
		m_renderable.IsVisible(false);
		TextureRegion* nullTexture = new TextureRegion(NULL, m_bound);
		m_renderable.SetTextureRegion(nullTexture);
		m_renderable.SetOrigin(Vector3(m_bound.left, m_bound.top, 1.0f));

		assert(Renderer::GetSingletonPtr());
		Renderer::GetSingleton().AddRenderable(&m_renderable);
	}
}