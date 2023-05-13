#pragma once
#include "SoundSystem.h"

class NullSoundSystem final : public SoundSystem
{
public:
	NullSoundSystem();
	~NullSoundSystem() = default;
	NullSoundSystem(const NullSoundSystem&) = delete;
	NullSoundSystem(NullSoundSystem&&) = delete;
	NullSoundSystem& operator= (const NullSoundSystem&) = delete;
	NullSoundSystem& operator= (const NullSoundSystem&&) = delete;

	void Update() override;
	void Play(const sound_id id, const float volume) override;
	void PauseSound() override;
	void UnpauseSound() override;
	void IncreaseVolume() override;
	void DecreaseVolume() override;
	void AddSound(const std::string& filename) override;
};

