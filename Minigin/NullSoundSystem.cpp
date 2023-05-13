#include "NullSoundSystem.h"

void dae::NullSoundSystem::Update()
{
}

void dae::NullSoundSystem::Play(const sound_id /*id*/, const float /* volume*/)
{
}

void dae::NullSoundSystem::PauseSound()
{
}

void dae::NullSoundSystem::UnpauseSound()
{
}

void dae::NullSoundSystem::IncreaseVolume()
{
}

void dae::NullSoundSystem::DecreaseVolume()
{
}

void dae::NullSoundSystem::AddSoundEffect(const std::string& /*filename*/, sound_id /*id*/)
{
}

void dae::NullSoundSystem::AddSoundMusic(const std::string& /*filename*/, sound_id /*id*/)
{
}
