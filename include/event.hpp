//
// EPITECH PROJECT, 2018
// event
// File description:
// event receiver
//

#pragma once

#include <irrlicht.h>
#include <irrKlang.h>
#include <iostream>
#include <time.h>
#include <unistd.h>
#include <ctime>

#define BTN_P1 1
#define BTN_P2 2
#define BTN_P3 3
#define BTN_P4 4
#define BTN_MORE 5
#define BTN_MINUS 6

#define WALL_PATH "./media/img/bomberWall2.jpg"
#define SPLASH_PATH "./media/img/splash.png"
#define WALL2_PATH "./media/img/wall2.jpg"
#define TFONT_PATH "./media/fonts/bigfont.png"
#define FONT_PATH "./media/fonts/fontlucida.png"
#define FONT2_PATH "./media/fonts/fontlucida.png"
#define FONT3_PATH "./media/fonts/bigfont.png"
#define MAP1_PATH "./media/img/imgMap1.jpg"
#define MAP2_PATH "./media/img/imgMap1.jpg"
#define MAP3_PATH "./media/img/imgMap1.jpg"
#define SOLO_PATH "./media/img/imgSolo.png"
#define DUO_PATH "./media/img/imgDuo.png"
#define TRIO_PATH "./media/img/imgTrio.png"
#define QUAD_PATH "./media/img/imgQuad.png"
#define HUMAN_PATH "./media/img/imgHuman.png"
#define IA_PATH "./media/img/imgIA.png"
#define EMPTY_PATH "./media/img/imgEmpty.png"
#define MORE_PATH "./media/img/imgMore.png"
#define MINUS_PATH "./media/img/imgMinus.png"
#define MUSIC_PATH "./media/sounds/menu_theme.wav"
#define CLIC_PATH "media/sounds/clic.wav"

typedef enum Type
{
	EMPT = 0,
	HUMAN = 1,
	IA = 2
} Type;

typedef struct Players
{
	int nb_P;
	Type P1;
	Type P2;
	Type P3;
	Type P4;
} Players;

class MenuEventReceiver : public irr::IEventReceiver
{
public:
	MenuEventReceiver(Players players);
	virtual bool OnEvent(const irr::SEvent &event);
	Players updatePlayers(void);
	void setEngine(irrklang::ISoundEngine *engine);
private:
	void addPlayer(void);
	void delPlayer(void);
	void switchState(int np);
	void playSound(void);
	irrklang::ISoundEngine *_engine;
	irrklang::ISound *_clic;
	Players _players;
};
