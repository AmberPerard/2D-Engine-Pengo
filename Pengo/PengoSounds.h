#pragma once
#include <string>
#include <unordered_map>

enum Sounds
{
	MAIN_SONG,
	START_SONG,
	END_SONG,
	CREDITS,
	DESTORY_BLOCK,
	MISS,
	PUNCH_BLOCK,
	ENEMY_WALK_KILL,
	ENEMY_BLOCK_KILL
};

static std::unordered_map PengoSounds{
	std::pair{MAIN_SONG, std::string{"../Data/Sound/MainSong.mp3"}},
	std::pair{PUNCH_BLOCK, std::string{"../Data/Sound/BlockPunch.wav"}}
};
