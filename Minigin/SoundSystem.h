#pragma once
#include <string>

namespace dae
{

	using sound_id = unsigned short;

	class SoundSystem
	{
	public:
		virtual ~SoundSystem() = default;

		virtual void Update() = 0;
		virtual void Play(const sound_id id, const float volume) = 0;
		virtual void PauseSound() = 0;
		virtual void UnpauseSound() = 0;
		virtual void IncreaseVolume() = 0;
		virtual void DecreaseVolume() = 0;
		virtual void AddSound(const std::string& filename) = 0;
	};
}