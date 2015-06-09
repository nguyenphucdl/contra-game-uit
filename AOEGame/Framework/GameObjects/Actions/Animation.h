#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include "../../Application/Context.h"
#include "../../Renderer/Texture/TextureRegion.h"
#include "../../Utilities/AnimCache.h"

namespace Framework
{
	class Animation
	{
	private:
		typedef std::vector<TextureRegion*>			TextureRegionVector;
		typedef TextureRegionVector::iterator		TextureRegionVectorIterator;

		TextureRegionVector				m_frames;
		std::string						m_name;
		float							m_elapse;
		float							m_delay;
		int								m_curIdx;
	public:
		explicit Animation(std::string name, float delay);
		virtual ~Animation();

		TextureRegion*	Next();
		TextureRegion*  Current();

		void	SetTimeDelay(float delay)			{ m_delay = delay; }
		float	GetTimeDelay()						{ return m_delay; }
		void	SetName(std::string name)			{ m_name = name; }
		const std::string& GetName()				{ return m_name; }
		void	SetFrameIndex(int idx);
		void	Reverse();
		int		GetFrameIndex()						{ return m_curIdx; }		
		void	AddFrame(TextureRegion* frame);
		void	Reset()								{ m_curIdx = 0; }

	public:
		//static Animation* CreateAnimation(std::string name, float delay, Texture* sheet, int dimensionx, int dimensiony, int framecounts, int offset, bool flipX = false);
		/*static Animation* CreateAnimation(std::string name, float delay, Texture* sheet, int dimensionx, int dimensiony, int framecounts);*/
		//static Animation* CreateAnimation(std::string name, float delay, Texture* sheet, int dimensionx, int dimensiony, int framecounts, int offset, bool reverse);
		static Animation* CreateAnimation(std::string key, AnimCache* propertyList, float delay, int offset, int framecounts, bool flipx = false);
		static Animation* CreateAnimation(std::string key, AnimCache* propertyList, float delay, int offset, int framecounts, bool flipx, bool reverse);
	};
}

#endif//__INPUT_H__