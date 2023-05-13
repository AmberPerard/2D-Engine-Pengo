#include "SoundLoggerSystem.h"

#include <iostream>

dae::SoundLoggerSystem::SoundLoggerSystem(std::unique_ptr<SoundSystem>&& ss)
	: _real_ss{std::move(ss)}
{
	std::cout << "SoundLoggerSystem created" << std::endl;
}

void dae::SoundLoggerSystem::Update()
{
	_real_ss->Update();
	std::cout << "SoundLoggerSystem updated" << std::endl;
}

void dae::SoundLoggerSystem::Play(const sound_id id, const float volume, SoundType soundType)
{
	_real_ss->Play(id, volume, soundType);
	std::cout << "playing " << id << " at volume " << volume << std::endl;
}

void dae::SoundLoggerSystem::PauseSound()
{
	_real_ss->PauseSound();
	std::cout << "Paused current playing sound" << std::endl;
}

void dae::SoundLoggerSystem::UnpauseSound()
{
	_real_ss->UnpauseSound();
	std::cout << "unPaused current playing sound" << std::endl;
}

void dae::SoundLoggerSystem::IncreaseVolume()
{
	_real_ss->IncreaseVolume();
	std::cout << "increase the volume of current playing sound" << std::endl;
}

void dae::SoundLoggerSystem::DecreaseVolume()
{
	_real_ss->DecreaseVolume();
	std::cout << "decrease the volume of current playing sound" << std::endl;
}

void dae::SoundLoggerSystem::AddSoundMusic(const std::string& filename, sound_id id)
{
	_real_ss->AddSoundMusic(filename,id);
	std::cout << "Added the sound with filename as music: " << filename << std::endl;
}

void dae::SoundLoggerSystem::AddSoundEffect(const std::string& filename, sound_id id)
{
	_real_ss->AddSoundEffect(filename,id);
	std::cout << "Added the sound with filename as soundEffect: " << filename << std::endl;
}
