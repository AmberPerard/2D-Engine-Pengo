#pragma once
#include "SoundSystem.h"

namespace dae
{
	class NullSoundSystem final : public SoundSystem
	{
	public:
		NullSoundSystem() = default;
		~NullSoundSystem() = default;
		NullSoundSystem(const NullSoundSystem&) = delete;
		NullSoundSystem(NullSoundSystem&&) = delete;
		NullSoundSystem& operator= (const NullSoundSystem&) = delete;
		NullSoundSystem& operator= (const NullSoundSystem&&) = delete;

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
