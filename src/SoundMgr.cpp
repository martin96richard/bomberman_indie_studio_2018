//
// EPITECH PROJECT, 2018
// Indie_studio
// File description:
// Sound Manager
//

#include "SoundMgr.hpp"

SoundMgr::SoundMgr()
{
	_engine = irrklang::createIrrKlangDevice();
}

SoundMgr::~SoundMgr()
{
}

void SoundMgr::playMusic(void)
{
	_music = _engine->play2D(THEME_PATH, true, false, true,
				 irrklang::ESM_AUTO_DETECT, true);
}

void SoundMgr::stopMusic(void)
{
	_music->stop();
	_music->drop();
}

void SoundMgr::closeSMgr(void)
{
	_engine->drop();
}

void SoundMgr::playSound(Stype type)
{
	switch (type)
	{
	case EXPLODE:
		_engine->play2D(SEXP_PATH, false, false, true,
				irrklang::ESM_AUTO_DETECT, false);
		break;
	case FUSE:
		_engine->play2D(SFUS_PATH, false, false, true,
				irrklang::ESM_AUTO_DETECT, false);
		break;
	case GMOVER:
		_engine->play2D(SGVER_PATH, false, false, true,
				irrklang::ESM_AUTO_DETECT, false);
		break;
	case POWUP:
		_engine->play2D(SPWUP_PATH, false, false, true,
				irrklang::ESM_AUTO_DETECT, false);
		break;
	default:
		break;
	}
}
