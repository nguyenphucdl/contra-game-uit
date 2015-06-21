#include "AudioManager.h"

namespace Framework
{
	Sample::Sample()
	{
	}

	Sample::~Sample()
	{
		if (m_sample != NULL) {
			FMOD_Sound_Release(m_sample);
			m_sample = NULL;
		}
	}

	AudioManager::AudioManager(const unsigned int priority)
		: Task(priority, "Audio manager Task")
		, m_system(NULL)
		, m_samples(50)
	{
	}

	AudioManager::~AudioManager()
	{
		// release all samples
		for (AudioSampleVectorIterator it = m_samples.begin(); it != m_samples.end(); it++)
		{
			(*it) = NULL;
		}
		FMOD_System_Release(m_system);
	}

	bool AudioManager::_Init()
	{
		if (FMOD_System_Create(&m_system) != FMOD_OK) {
			return false;
		}

		if (FMOD_System_Init(m_system, 100, FMOD_INIT_NORMAL, NULL) != FMOD_OK) {
			return false;
		}
		return true;
	}

	bool AudioManager::Load(std::string filename, std::string name)
	{
		if (filename.length() == 0 || name.length() == 0) return false;

		Sample* sample = new Sample();
		sample->setName(name);

		try {
			FMOD_RESULT res;
			res = FMOD_System_CreateSound(
				m_system,			//FMOD system
				filename.c_str(),	//filename
				FMOD_DEFAULT,		//default audio
				NULL,				//n/a
				&sample->m_sample);	//pointer to sample

			if (res != FMOD_OK) {
				return false;
			}
		}
		catch (...) {
			return false;
		}
		m_samples.push_back(sample);

		return true;
	}

	Sample* AudioManager::Load(std::string filename)
	{
		if (filename.length() == 0) return false;

		Sample* sample = new Sample();
		try {
			FMOD_RESULT res;
			res = FMOD_System_CreateSound(
				m_system,			//FMOD system
				filename.c_str(),	//filename
				FMOD_DEFAULT,		//default audio
				NULL,				//n/a
				&sample->m_sample);	//pointer to sample

			if (res != FMOD_OK) {
				sample = NULL;
			}
		}
		catch (...) {
			sample = NULL;
		}
		return sample;
	}

	bool AudioManager::Play(std::string name)
	{
		FMOD_RESULT res;
		Sample* sample = FindSample(name);
		//*** BUG
		if (!sample) return false;

		if (sample->m_sample != NULL) {
			try {
				//sample found, play it
				res = FMOD_System_PlaySound(
					m_system,
					FMOD_CHANNEL_FREE,
					sample->m_sample,
					true,
					&sample->m_channel);

				if (res != FMOD_OK) return false;

				FMOD_Channel_SetLoopCount(sample->m_channel, -1);
				FMOD_Channel_SetPaused(sample->m_channel, false);
			}
			catch (...) {
				return false;
			}
		}
		return true;
	}

	bool AudioManager::Play(Sample *sample)
	{
		FMOD_RESULT res;
		if (sample == NULL) return false;
		if (sample->m_sample == NULL) return false;

		try {
			res = FMOD_System_PlaySound(
				m_system,
				FMOD_CHANNEL_FREE,
				sample->m_sample,
				true,
				&sample->m_channel);

			if (res != FMOD_OK) return false;

			FMOD_Channel_SetLoopCount(sample->m_channel, -1);
			FMOD_Channel_SetPaused(sample->m_channel, false);
		}
		catch (...) {
			return false;
		}
		return true;
	}

	void AudioManager::Stop(std::string name)
	{
		if (!IsPlaying(name)) return;

		Sample* sample = FindSample(name);
		if (sample == NULL) return;

		FMOD_Channel_Stop(sample->m_channel);
	}

	void AudioManager::StopAll()
	{
		for (AudioSampleVectorIterator it = m_samples.begin(); it != m_samples.end(); ++it)
		{
			FMOD_Channel_Stop((*it)->m_channel);
		}
	}

	void AudioManager::StopAllExcept(std::string name)
	{
		for (AudioSampleVectorIterator it = m_samples.begin(); it != m_samples.end(); ++it)
		{
			if ((*it)->getName() != name)
			{
				FMOD_Channel_Stop((*it)->m_channel);
			}
		}
	}

	bool AudioManager::IsPlaying(std::string name)
	{
		Sample* samp = FindSample(name);
		if (samp == NULL) return false;

		int index;
		FMOD_Channel_GetIndex(samp->m_channel, &index);

		// FMOD returns 99 if sample is playing, 0 if not
		return (index > 0);
	}

	bool AudioManager::SampleExists(std::string name)
	{
		for (AudioSampleVectorIterator it = m_samples.begin(); it != m_samples.end(); ++it)
		{
			if ((*it)->getName() == name)
			{
				return true;
			}
		}

		return false;
	}

	Sample *AudioManager::FindSample(std::string name)
	{
		Sample* sample = NULL;
		for (AudioSampleVectorIterator it = m_samples.begin(); it != m_samples.end(); ++it)
		{
			if ((*it)->getName() == name)
			{
				sample = (*it);
				break;
			}
		}
		return sample;
	}

	bool AudioManager::Start()
	{
		return _Init();
	}

	void AudioManager::OnSuspend()
	{

	}

	void AudioManager::Update()
	{
		FMOD_System_Update(m_system);
	}

	void AudioManager::OnResume()
	{

	}

	void AudioManager::Stop()
	{

	}
}