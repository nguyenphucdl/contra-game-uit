#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include "../../Application/Context.h"
#include "../../Renderer/Texture/TextureRegion.h"

namespace Framework
{
	class Animation
	{
	private:
		std::string						m_name;
		std::vector<TextureRegion*>		m_frames;
		float							m_elapse;
		float							m_delay;
		int								m_curIdx;
	public:
		explicit Animation(std::string name, float delay);
		virtual ~Animation();

		TextureRegion*	Next();
		TextureRegion*  Current();

		void	SetTimeDelay(float delay)	{ m_delay = delay; }
		float	GetTimeDelay()				{ return m_delay; }
		void	SetName(std::string name)	{ m_name = name; }
		std::string GetName()				{ return m_name; }
		void	SetFrameIndex(int idx);
		int		GetFrameIndex()			{ return m_curIdx; }		
		void	AddFrame(TextureRegion* frame);

	public:
		static Animation* CreateAnimation(std::string name, float delay, Texture* sheet, int dimensionx, int dimensiony, int framecounts, int offset);
		static Animation* CreateAnimation(std::string name, float delay, Texture* sheet, int dimensionx, int dimensiony, int framecounts);
	};
}

#endif//__INPUT_H__