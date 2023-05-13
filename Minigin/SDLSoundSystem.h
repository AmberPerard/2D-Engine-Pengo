#pragma once
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
		class SDLSoundSystemImpl;
		SDLSoundSystemImpl* pImpl{};

	public:
		SDLSoundSystem();
		~SDLSoundSystem() override;
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
	};
}
