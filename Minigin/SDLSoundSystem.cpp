#include "SDLSoundSystem.h"
#include <iostream>


dae::SDLSoundSystem::SDLSoundSystem()
{
	// Initialize SDL_mixer
	Mix_Init(MIX_INIT_MP3);
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
		return;
	}
	m_SoundThread = std::jthread(&SDLSoundSystem::Update, this);
}

dae::SDLSoundSystem::~SDLSoundSystem()
{
	m_isRunning = false;
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

void dae::SDLSoundSystem::Update()
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
					Mix_PlayMusic(m_SoundMusic[message.id], 0);
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
					Mix_PlayChannel(-1, m_SoundEffects[message.id], 0);
					break;
				}
				}
			}
		}
	}
}

void dae::SDLSoundSystem::Play(const sound_id id, const float volume, SoundType soundType)
{
	std::lock_guard lock(m_audioEventMutex);
	m_SoundQueue.push(SoundMessage{ id, volume,soundType });
	m_SoundCV.notify_all();
}

void dae::SDLSoundSystem::PauseSound()
{
}

void dae::SDLSoundSystem::UnpauseSound()
{
}

void dae::SDLSoundSystem::IncreaseVolume()
{
}

void dae::SDLSoundSystem::DecreaseVolume()
{
}

void dae::SDLSoundSystem::AddSoundEffect(const std::string& filename, sound_id id)
{
	std::lock_guard lock(m_audioEventMutex);
	m_SoundsToLoad[id] = filename;
}

void dae::SDLSoundSystem::AddSoundMusic(const std::string& filename, sound_id id)
{
	std::lock_guard lock(m_audioEventMutex);
	m_SoundsToLoad[id] = filename;
}