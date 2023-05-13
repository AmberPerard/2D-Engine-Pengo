#include "ServiceManager.h"

std::unique_ptr<dae::SoundSystem> dae::ServiceManager::_ss_instance{ std::make_unique<NullSoundSystem>() };