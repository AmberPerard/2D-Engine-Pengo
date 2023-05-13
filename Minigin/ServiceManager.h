#pragma once
#include <algorithm>
#include <memory>

#include "NullSoundSystem.h"
#include "SoundSystem.h"

namespace dae
{
	class ServiceManager final
	{
		static std::unique_ptr<SoundSystem> _ss_instance;
	public:
		~ServiceManager() = default;
		static SoundSystem& get_sound_system() { return *_ss_instance; }
		static void register_sound_system(std::unique_ptr<SoundSystem>&& ss) {
			_ss_instance = ss == nullptr ? std::make_unique<NullSoundSystem>() : std::move(ss);
		}
	};
}
