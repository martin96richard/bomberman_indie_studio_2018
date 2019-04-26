//
// EPITECH PROJECT, 2018
// Indie_Studio
// File description:
// Sound Manager
//

#pragma once

#include <irrKlang.h>

#define SEXP_PATH "./media/sounds/explosion.wav"
#define SFUS_PATH "./media/sounds/fuse.wav"
#define SGVER_PATH "./media/sounds/game_over.wav"
#define SPWUP_PATH "./media/sounds/power_up.wav"
#define THEME_PATH "./media/sounds/game_theme.wav"

typedef enum Stype
{
	NOTHING = 0,
	EXPLODE = 1,
	FUSE	= 2,
	GMOVER	= 3,
	POWUP	= 4
} Stype;

class SoundMgr
{
public:
	SoundMgr();
	~SoundMgr();

	void playSound(Stype type);
	void playMusic(void);
	void stopMusic(void);
	void closeSMgr(void);
private:
	irrklang::ISound *_music;
	irrklang::ISoundEngine	*_engine;
};
