/*
** EPITECH PROJECT, 2018
** displayGame
** File description:
** Displaying game features
*/

#pragma once

#include "MyEventReceiver.hpp"
#include "game.hpp"
#include "menu.hpp"
#include "event.hpp"

#define GRASS_PATH "./media/img/grass.jpg"
#define CRATE_PATH "./media/img/crate.png"
#define BLOCK_PATH "./media/img/wall.bmp"
#define BOMB_UP "./media/img/bomb_up.png"
#define FIRE_UP "./media/img/fire_up.png"
#define SPEED_UP "./media/img/speed_up.png"
#define FIRE_PATH "./media/img/fire.jpg"
#define GOVER_PATH "./media/img/gameOver.png"
#define KEYP1_PATH "./media/img/keysP1.png"
#define KEYP2_PATH "./media/img/keysP2.png"
#define ESC_PATH "./media/img/escape.png"
#define BOMB3D_PATH "./media/3Dmodels/Bomb.3ds"
#define BOMBTEX_PATH "./media/img/bombTexture.png"
#define BMAN3D_PATH "./media/3Dmodels/BomberMan.3ds"
#define BMANTEX_PATH "./media/img/Bombermap.tga"
#define FONTSCORE_PATH "./media/font/fontlucida.png"
#define IRR_SIZE 10

class DisplayGame
{

public:
	DisplayGame(GameConfig game_config);
	~DisplayGame();

	bool handleAll(void);
	void quit(void);
private:
	int setScreen(void);
	std::pair<int, int> eventHandler(void);
	irr::IrrlichtDevice* getDevice(void);
	irr::video::IVideoDriver* getDriver(void);
	irr::scene::ISceneManager* getScene(void);
	std::vector<irr::scene::IAnimatedMeshSceneNode *> getModel(void);
	void setModel(void);
	void loadTextures(void);
	void addFloor(void);
	bool gameOver(void);

	void buildPowerup(int id, float x, float y , tiletype type);
	void buildBlock(int id, float x, float y, tiletype type);
	void buildBomb(int id, float x, float y, tiletype type);
	void buildPlayer(std::vector<player> player, int nb_players);
	void setTexture(int id, tiletype type);
	void updateTexture(int id, tiletype type);
	void updateMap(std::vector<std::vector<items>> map);
	void buildMap(std::vector<std::vector<items>> map);
	void displayScore(void);
	void displayKeys(void);
	
	irr::IrrlichtDevice *_device;
	irr::video::IVideoDriver *_driver;
	irr::scene::ISceneManager *_sceneMgr;
	irr::gui::IGUIEnvironment *_guiEnv;
	irr::gui::ICursorControl *_cursor;
	irr::core::position2d<int> _posCursor;

	irr::video::SMaterial *_material;
	std::vector<irr::scene::IAnimatedMeshSceneNode *> _sydney;
	irr::scene::IAnimatedMeshSceneNode *_bomb;
	irr::gui::IGUIFont *_font;

	irr::video::ITexture *_tblock;
	irr::video::ITexture *_tbreak;
	irr::video::ITexture *_tfloor;
	irr::video::ITexture *_tbombup;
	irr::video::ITexture *_tfireup;
	irr::video::ITexture *_tspeedup;
	irr::video::ITexture *_tfire;
	irr::video::ITexture *_tgover;
	irr::video::ITexture *_tkeyP1;
	irr::video::ITexture *_tkeyP2;
	irr::video::ITexture *_tesc;

	irr::scene::IMeshSceneNode *_floor;
	std::vector<irr::scene::IMeshSceneNode *> _bombs;
	std::vector<irr::scene::IMeshSceneNode *> _cubes;
	std::vector<irr::scene::IMeshSceneNode *> _powerups;

	game _game;
	MyEventReceiver _receiver;
	GameConfig _config;
	bool _rtomenu;
	bool _over;
	int _x = 10;
	int _y = 110;
	int _speed = 1;
};
