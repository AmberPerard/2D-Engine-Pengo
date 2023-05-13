#pragma once
#include "SoundSystem.h"

class SoundLoggerSystem final : public SoundSystem
{
public:
	SoundLoggerSystem();
	~SoundLoggerSystem() = default;
	SoundLoggerSystem(const SoundLoggerSystem&) = delete;
	SoundLoggerSystem(SoundLoggerSystem&&) = delete;
	SoundLoggerSystem& operator= (const SoundLoggerSystem&) = delete;
	SoundLoggerSystem& operator= (const SoundLoggerSystem&&) = delete;

	void Update() override;
	void Play(const sound_id id, const float volume) override;
	void PauseSound() override;
	void UnpauseSound() override;
	void IncreaseVolume() override;
	void DecreaseVolume() override;
	void AddSound(const std::string& filename) override;
};

