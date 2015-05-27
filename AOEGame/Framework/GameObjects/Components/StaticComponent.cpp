#include "StaticComponent.h"
#include "../../Renderer/Renderer.h"
namespace Framework
{
	StaticComponent::StaticComponent(GameObject* pOwner)
		: RenderableComponent(pOwner)
	{
	}

	StaticComponent::~StaticComponent()
	{
	}

	void StaticComponent::Initialize()
	{
		m_renderable.SetZIndex(1000);
		m_renderable.SetDebug(true);
		m_renderable.Show(false);

		RECT bound;
		bound.left = m_renderable.GetTransform().GetTranslation().m_x;
		bound.right = bound.left + m_renderable.GetWidth();
		bound.top = m_renderable.GetTransform().GetTranslation().m_y;
		bound.bottom = bound.top + m_renderable.GetHeight();

		TextureRegion* nullTexture = new TextureRegion(NULL, bound);
		m_renderable.SetTextureRegion(nullTexture);
		
		m_renderable.SetUseBounds(true);
		m_renderable.SetBoundMin(Vector3(0.0f, 0.0f, 1.0f));
		m_renderable.SetBoundMax(Vector3(m_renderable.GetWidth(), m_renderable.GetHeight(), 1.0f));
		
		m_renderable.SetRenderTransform(true);

		assert(Renderer::GetSingletonPtr());
		Renderer::GetSingleton().AddRenderable(&m_renderable);
	}
}