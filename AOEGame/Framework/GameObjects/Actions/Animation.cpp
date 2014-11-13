#include "Animation.h"
#include "../../Utilities/Timer.h"

namespace Framework
{
	Animation::Animation(std::string name, float delay)
		: m_name(name)
		, m_delay(delay)
		, m_curIdx(-1)
		, m_elapse(0)
		, m_frames()
	{
	}

	Animation::~Animation()
	{
	}

	void Animation::SetFrameIndex(int idx)
	{
		if (idx > -1 && idx < m_frames.size())
			m_curIdx = idx;
		else
		{
			Log::info(Log::LOG_LEVEL_MIN, "Attempt to set invalid frame index!");
		}
	}

	void Animation::AddFrame(TextureRegion* frame)
	{
		m_frames.push_back(frame);
	}

	TextureRegion* Animation::Current()
	{
		return m_frames.at(m_curIdx);
	}

	TextureRegion* Animation::Next()
	{
		m_elapse += Timer::GetSingletonPtr()->GetTimeSim();
		//Log::info(Log::LOG_LEVEL_MEDIUM, "Animation elapse: %f\n", m_elapse);
		if (m_elapse > m_delay)
		{
			m_curIdx++;
			if (m_curIdx > m_frames.size() - 1)
				m_curIdx = 0;

			//Log::info(Log::LOG_LEVEL_MEDIUM, "Animation update at %f\n", m_elapse);
			m_elapse = 0;
		}
		return m_frames.at(m_curIdx);
	}

	Animation* Animation::CreateAnimation(std::string name, float delay, Texture* sheet, int dimensionx, int dimensiony, int framecounts)
	{
		return Animation::CreateAnimation(name, delay, sheet, dimensionx, dimensiony, framecounts, 0);
	}

	Animation* Animation::CreateAnimation(std::string name, float delay, Texture* sheet, int dimensionx, int dimensiony, int framecounts, int offset)
	{
		Animation *anim = new Animation(name, delay);

		int frwidth = sheet->GetWidth() / dimensionx;
		int frheight = sheet->GetHeight() / dimensiony;

		RECT frRect;

		int add = 0,count = 0;

		for (int j = 0; j < dimensiony; j++)
		{
			for (int i = 0; i < dimensionx; i++)
			{
				count++;
				if (count > offset && add < framecounts)
				{
					frRect.left = i * frwidth;
					frRect.right = frRect.left + frwidth;
					frRect.top = j * frheight;
					frRect.bottom = frRect.top + frheight;

					TextureRegion* region = new TextureRegion(sheet, frRect);
					anim->AddFrame(region);
					add++;
				}
			}
		}
		anim->SetFrameIndex(0);
		return anim;
	}
}