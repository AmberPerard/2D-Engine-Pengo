#pragma once
#include <memory>

#include "SoundSystem.h"
namespace dae
{
	class SoundLoggerSystem final : public SoundSystem
	{
	private:
		std::unique_ptr<SoundSystem> _real_ss;

	public:
		SoundLoggerSystem(std::unique_ptr<SoundSystem>&& ss);
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
}
