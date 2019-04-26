//
// EPITECH PROJECT, 2018
// menu
// File description:
// menu hpp
//

#pragma once

#include "event.hpp"
#include <string>

#define MAX_NPLAYERS 4
#define MIN_NPLAYERS 2

typedef enum State
{
	INTRO = -1,
	MENU = 0,
	NEWGAME = 1,
	LOADGAME = 2,
	SETTINGS = 3
} State;

typedef struct GameConfig
{
	State state;
	Players *players;
} GameConfig;

class Menu
{
public:
	Menu();
	~Menu();

	bool runMenu(void);
	GameConfig getGameConfig(void);
private:
	Players getPlayers(void);
	irrklang::ISoundEngine *getEngine(void);
	irr::video::ITexture* getImgForNBPlayers(void);
	irr::video::ITexture* getPlayerSkin(int np);
	void setPlayers(Players players);
	void setFont(void);
	void setVisibility(void);
	void setIDs(void);
	void setToMenu(void);
	void setToNGame(void);
	void setToIntro(void);
	void updateGUI(void);
	void drawImages(void);
	void drawNGame(void);
	bool checkButtons(void);
	void loadTextures(void);
	void addElements(void);
	void playSound(void);
	void initMenu(void);

	State _state;
	Players _players;
	bool _play;
	std::time_t _begintime;

	irr::IrrlichtDevice *_device;
	irr::video::IVideoDriver *_driver;
	irr::scene::ISceneManager *_scnMgr;
	irr::gui::IGUIEnvironment *_guiEnv;
	irrklang::ISoundEngine *_engine;
	irrklang::ISound *_music;
	irrklang::ISound *_clic;

	irr::gui::ICursorControl *_cursor;
	irr::gui::IGUIFont *_font;
	irr::gui::IGUIFont *_fontTitle;
	irr::gui::IGUIFont *_font2;

	irr::gui::IGUIStaticText *_title;
	irr::gui::IGUIStaticText *_sTitlePlayers;
	irr::gui::IGUIStaticText *_sTitleMap;
	irr::gui::IGUIStaticText *_nbPlayers;

	irr::video::ITexture *_wallpaper;
	irr::video::ITexture *_splash;
	irr::video::ITexture *_wall2;
	irr::video::ITexture *_imgSolo;
	irr::video::ITexture *_imgDuo;
	irr::video::ITexture *_imgTrio;
	irr::video::ITexture *_imgQuad;
	irr::video::ITexture *_imgHuman;
	irr::video::ITexture *_imgIA;
	irr::video::ITexture *_imgEmpty;
	irr::video::ITexture *_imgMap1;
	irr::video::ITexture *_imgMap2;
	irr::video::ITexture *_imgMap3;
	irr::video::ITexture *_imgBtnMore;
	irr::video::ITexture *_imgBtnMinus;

	irr::gui::IGUIButton *_btnNgame;
	irr::gui::IGUIButton *_btnLgame;
	irr::gui::IGUIButton *_btnSettings;
	irr::gui::IGUIButton *_btnReturn;
	irr::gui::IGUIButton *_btnPlay;
	irr::gui::IGUIButton *_btnMore;
	irr::gui::IGUIButton *_btnMinus;
	irr::gui::IGUIButton *_btnP1;
	irr::gui::IGUIButton *_btnP2;
	irr::gui::IGUIButton *_btnP3;
	irr::gui::IGUIButton *_btnP4;
};
