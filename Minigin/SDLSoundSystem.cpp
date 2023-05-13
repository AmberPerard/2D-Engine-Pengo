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
	for (auto music : m_SoundMusic)
	{
		Mix_FreeMusic(music.second);
	}
	for (auto soundEffect : m_SoundEffects)
	{
		Mix_FreeChunk(soundEffect.second);
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
				for (const auto& sound : m_SoundEffects)
				{
					Mix_VolumeMusic((int)message.volume);
					if (sound.first == message.id)
					{
						Mix_PlayChannel(-1, sound.second, 0);
					}
				}

				for (const auto& sound : m_SoundMusic)
				{
					if (sound.first == message.id)
					{
						Mix_VolumeMusic((int)message.volume);
						if (Mix_PlayMusic(sound.second, 0) < 0)
						{
							std::cout << "Failed to play sound! SDL_mixer Error: " << Mix_GetError() << std::endl;
						}
					}
				}
			}
		}
	}
}

void dae::SDLSoundSystem::Play(const sound_id id, const float volume)
{
	std::lock_guard lock(m_audioEventMutex);
	m_SoundQueue.push(SoundMessage{ id, volume });
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
	Mix_Chunk* soundEffect = Mix_LoadWAV(filename.c_str());
	if (!soundEffect) {
		std::cout << "Sound effect could not be created, Error: " << Mix_GetError() << std::endl;
		return;
	}
	m_SoundEffects.push_back(std::make_pair(id, soundEffect));
}

void dae::SDLSoundSystem::AddSoundMusic(const std::string& filename, sound_id id)
{
	std::lock_guard lock(m_audioEventMutex);
	Mix_Music* mixMusic = Mix_LoadMUS(filename.c_str());
	if (!mixMusic) {
		std::cout << "Music could not be created, Error: " << Mix_GetError() << std::endl;
		return;
	}
	m_SoundMusic.push_back(std::make_pair(id, mixMusic));
}