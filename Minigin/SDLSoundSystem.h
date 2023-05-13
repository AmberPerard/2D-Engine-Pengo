#pragma once
#include <condition_variable>
#include <queue>
#include <SDL_mixer.h>
#include <thread>
#include <unordered_map>

#include "SoundSystem.h"
namespace dae
{	struct SoundMessage
	{
		sound_id id;
		float volume;
		SoundType soundType;
	};

	class SDLSoundSystem final : public SoundSystem
	{
	public:
		SDLSoundSystem();
		~SDLSoundSystem();
		SDLSoundSystem(const SDLSoundSystem&) = delete;
		SDLSoundSystem(SDLSoundSystem&&) = delete;
		SDLSoundSystem& operator= (const SDLSoundSystem&) = delete;
		SDLSoundSystem& operator= (const SDLSoundSystem&&) = delete;

		void Update() override;
		void Play(const sound_id id, const float volume, SoundType soundType) override;
		void PauseSound() override;
		void UnpauseSound() override;
		void IncreaseVolume() override;
		void DecreaseVolume() override;
		void AddSoundEffect(const std::string& filename, sound_id id) override;
		void AddSoundMusic(const std::string& filename, sound_id id) override;

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

	};
}
