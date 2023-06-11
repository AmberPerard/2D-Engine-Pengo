#pragma once
#include <string>
#include <unordered_map>

enum Sounds
{
	START,
	MAIN_SONG,
	START_SONG,
	END_SONG,
	DESTORY_BLOCK,
	STOP_BLOCK,
	LOST,
	ENEMY_WALK_KILL,
	ENEMY_BLOCK_KILL,
	DYING
};

static std::unordered_map PengoSounds{
	std::pair{START, std::string{"../Data/Sound/Start.mp3"}},
	std::pair{MAIN_SONG, std::string{"../Data/Sound/MainSong.mp3"}},
	std::pair{START_SONG, std::string{"../Data/Sound/Act_Start.mp3"}},
	std::pair{END_SONG, std::string{"../Data/Sound/Act_End.mp3"}},
	std::pair{DESTORY_BLOCK, std::string{"../Data/Sound/BlockDestroy.wav"}},
	std::pair{STOP_BLOCK, std::string{"../Data/Sound/BlockStop.mp3"}},
	std::pair{LOST, std::string{"../Data/Sound/Lost.wav"}},
	std::pair{ENEMY_BLOCK_KILL, std::string{"../Data/Sound/EnemyKill.wav"}},
	std::pair{DYING, std::string{"../Data/Sound/Dying.wav"}},
};
