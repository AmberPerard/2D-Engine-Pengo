#include "SDLSoundSystem.h"

#include <condition_variable>
#include <iostream>
#include <queue>
#include <thread>
#include <unordered_map>
#include <SDL_mixer.h>


using namespace dae;

class SDLSoundSystem::SDLSoundSystemImpl final
{
private:
	//separate sound thread
	std::jthread m_SoundThread;
	std::condition_variable m_SoundCV;

	std::mutex m_audioEventMutex;
	std::queue<SoundMessage> m_SoundQueue{};

	//storage for the sounds & effects
	std::unordered_map<sound_id, Mix_Chunk*> m_SoundEffects{};
	std::unordered_map<sound_id, Mix_Music*> m_SoundMusic{};

	std::unordered_map<sound_id, std::string> m_SoundsToLoad{};

	bool m_isRunning = true;
public:
	SDLSoundSystemImpl()
	{
		// Initialize SDL_mixer
		Mix_Init(MIX_INIT_MP3);
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			std::cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
			return;
		}
		m_SoundThread = std::jthread(&SDLSoundSystemImpl::Update, this);
	}
	~SDLSoundSystemImpl()
	{
		m_isRunning = false;
		m_SoundCV.notify_one();

		for (auto music : m_SoundMusic)
		{
			Mix_FreeMusic(music.second);
			music.second = nullptr; // Set the pointer to nullptr after freeing the memory
		}
		for (auto soundEffect : m_SoundEffects)
		{
			Mix_FreeChunk(soundEffect.second);
			soundEffect.second = nullptr; // Set the pointer to nullptr after freeing the memory
		}

		Mix_CloseAudio();
		Mix_Quit();
	}
	void Update()
	{
		while (m_isRunning)
		{
			// Wait for an audio event
			std::unique_lock lock(m_audioEventMutex);
			m_SoundCV.wait(lock, [&] { return !m_SoundQueue.empty() || !m_isRunning; });

			if (!m_SoundQueue.empty())
			{

				for (size_t i{}; i < m_SoundQueue.size(); ++i)
				{
					const auto& message = m_SoundQueue.front();
					m_SoundQueue.pop();
					lock.unlock();

					switch (message.soundType)
					{
					case Music:
					{
						Mix_VolumeMusic((int)message.volume);
						if (m_SoundMusic[message.id] == nullptr)
						{
							Mix_Music* musicEffect = Mix_LoadMUS(m_SoundsToLoad[message.id].c_str());
							m_SoundMusic[message.id] = musicEffect;
						}
						Mix_PlayMusic(m_SoundMusic[message.id], -1);
						break;
					}
					case Effect:
					{
						Mix_Volume(-1, (int)message.volume);
						if (m_SoundEffects[message.id] == nullptr)
						{
							Mix_Chunk* soundEffect = Mix_LoadWAV(m_SoundsToLoad[message.id].c_str());
							m_SoundEffects[message.id] = soundEffect;
						}
						Mix_PlayChannel(1, m_SoundEffects[message.id], 0);
						break;
					}
					}
				}
			}
		}
	}
	void Play(const sound_id id, const float volume, SoundType soundType)
	{
		std::lock_guard lock(m_audioEventMutex);
		m_SoundQueue.push(SoundMessage{ id, volume,soundType });
		m_SoundCV.notify_one();
	}

	void PauseSound()
	{
		// Pause all active sound channels
		for (int i = 0; i < MIX_CHANNELS; i++) {
			if (Mix_Playing(i)) {
				Mix_Pause(i);
			}
		}
		// Pause music channels
		Mix_PauseMusic();
	}
	void UnpauseSound()
	{
		// Unpause all paused sound channels
		for (int i = 0; i < MIX_CHANNELS; i++) {
			if (Mix_Paused(i)) {
				Mix_Resume(i);
			}
		}
		// Pause music channels
		Mix_ResumeMusic();
	}
	void IncreaseVolume()
	{
		// Increase the volume for all active sound channels
		for (int i = 0; i < MIX_CHANNELS; i++) {
			if (Mix_Playing(i)) {
				int currentVolume = Mix_Volume(i, -1);
				Mix_Volume(i, ++currentVolume);
			}
		}
		if (Mix_PlayingMusic())
		{
			int currentVolume = Mix_VolumeMusic(-1);
			Mix_VolumeMusic(--currentVolume);
		}
	}
	void DecreaseVolume()
	{
		// decrease the volume for all active sound channels
		for (int i = 0; i < MIX_CHANNELS; i++) {
			if (Mix_Playing(i)) {
				int currentVolume = Mix_Volume(i, -1);
				Mix_Volume(i, --currentVolume);
			}
		}
		if (Mix_PlayingMusic())
		{
			int currentVolume = Mix_VolumeMusic(-1);
			Mix_VolumeMusic(--currentVolume);
		}
	}
	void AddSoundEffect(const std::string& filename, sound_id id)
	{
		std::lock_guard lock(m_audioEventMutex);
		m_SoundsToLoad[id] = filename;
	}
	void AddSoundMusic(const std::string& filename, sound_id id)
	{
		std::lock_guard lock(m_audioEventMutex);
		m_SoundsToLoad[id] = filename;
	}
};



dae::SDLSoundSystem::SDLSoundSystem()
{
	pImpl = new SDLSoundSystemImpl();
}

dae::SDLSoundSystem::~SDLSoundSystem()
{
	delete pImpl;
}

void dae::SDLSoundSystem::Update()
{
	pImpl->Update();
}

void dae::SDLSoundSystem::Play(const sound_id id, const float volume, SoundType soundType)
{
	pImpl->Play(id, volume, soundType);
}

void dae::SDLSoundSystem::PauseSound()
{
	pImpl->PauseSound();
}

void dae::SDLSoundSystem::UnpauseSound()
{
	pImpl->UnpauseSound();
}

void dae::SDLSoundSystem::IncreaseVolume()
{
	pImpl->IncreaseVolume();
}

void dae::SDLSoundSystem::DecreaseVolume()
{
	pImpl->DecreaseVolume();
}

void dae::SDLSoundSystem::AddSoundEffect(const std::string& filename, sound_id id)
{
	pImpl->AddSoundEffect(filename, id);
}

void dae::SDLSoundSystem::AddSoundMusic(const std::string& filename, sound_id id)
{
	pImpl->AddSoundMusic(filename, id);
}