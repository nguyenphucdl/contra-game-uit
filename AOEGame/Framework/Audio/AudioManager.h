#ifndef __AUDIO_MANAGER_H__
#define __AUDIO_MANAGER_H__

#include "../Application/Context.h"
#include "../Kernel/Task.h"
#include "../Lib/fmod/inc/fmod.hpp"


namespace Framework
{
	class Sample
	{
	private:
		std::string m_name;

	public:
		FMOD_SOUND* m_sample;
		FMOD_CHANNEL* m_channel;

	public:
		Sample(void);
		~Sample(void);
		std::string getName() { return m_name; }
		void setName(std::string value) { m_name = value; }
	};


	class AudioManager 
		: public Singleton<AudioManager>
		, public Task
	{
	private:
		typedef std::vector<Sample*>			AudioSampleVector;
		typedef AudioSampleVector::iterator		AudioSampleVectorIterator;

		FMOD_SYSTEM*		m_system;
		AudioSampleVector	m_samples;

	private:
		bool _Init();
		
	public:
		AudioManager(const unsigned int priority);
		~AudioManager();

		bool Load(std::string filename, std::string name);
		Sample* Load(std::string filename);
		bool Play(std::string name);
		bool Play(Sample *sample);
		void Stop(std::string name);
		void StopAll();
		void StopAllExcept(std::string name);

		bool IsPlaying(std::string name);
		bool SampleExists(std::string name);
		Sample *FindSample(std::string name);


		bool	Start();
		void	OnSuspend();
		void	Update();
		void	OnResume();
		void	Stop();
	};
}

#endif