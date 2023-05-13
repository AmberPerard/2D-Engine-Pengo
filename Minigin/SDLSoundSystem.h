#pragma once
#include <condition_variable>
#include <queue>
#include <SDL_mixer.h>
#include <thread>

#include "SoundSystem.h"
namespace dae
{
	enum Type
	{
		SoundEffect,
		Music
	};

	struct SoundMessage
	{
		sound_id id;
		float volume;
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
		void Play(const sound_id id, const float volume) override;
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

		//pairs for the queue
		using SoundEffect = std::pair<sound_id, Mix_Chunk*>;
		using SoundMusic = std::pair<sound_id, Mix_Music*>;

		//storage for the sounds & effects
		std::vector<SoundEffect> m_SoundEffects{};
		std::vector<SoundMusic> m_SoundMusic{};

		bool m_isRunning = true;

	};
}
