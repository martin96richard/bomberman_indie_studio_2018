//
// EPITECH PROJECT, 2018
// displayGame
// File description:
// Displaying map and players
//

#include "DisplayGame.hpp"

DisplayGame::DisplayGame(GameConfig game_config)
{
	_device = irr::createDevice(irr::video::EDT_OPENGL,
				    irr::core::dimension2d<irr::u32>
				    (1920, 1080), 32, false, false
				    , false, &_receiver);
	_driver = _device->getVideoDriver();
	_sceneMgr = _device->getSceneManager();
	_guiEnv = _device->getGUIEnvironment();
	_driver->setTextureCreationFlag(irr::video::ETCF_ALWAYS_32_BIT, true);
	_cursor = _device->getCursorControl();
	_posCursor = _cursor->getPosition();
	_config = game_config;
	_over = false;
	_rtomenu = false;
}

DisplayGame::~DisplayGame()
{
}

int DisplayGame::setScreen()
{
	_driver->beginScene(true, true, irr::video::SColor(155, 255, 20, 147));
	_font = _guiEnv->getFont(FONT3_PATH);

	if (!_device)
		return 1;
	return 0;
}

irr::IrrlichtDevice* DisplayGame::getDevice(void)
{
	return _device;
}

irr::video::IVideoDriver* DisplayGame::getDriver(void)
{
	return _driver;
}

irr::scene::ISceneManager* DisplayGame::getScene(void)
{
	return _sceneMgr;
}

std::vector<irr::scene::IAnimatedMeshSceneNode *> DisplayGame::getModel(void)
{
	return _sydney;
}

void DisplayGame::setModel(void)
{
	irr::core::vector3df pos(80, 60, -105);
	irr::core::vector3df rot(80, 60, 90);

	_sceneMgr->addCameraSceneNode(0, pos, rot, -1, true);
}

std::pair<int, int> DisplayGame::eventHandler(void)
{
	std::pair<int, int> actions;

	if (_receiver.IsKeyDown(irr::KEY_ESCAPE)) {
		if (!_over)
			_game.save();
		_device->closeDevice();
	}
	if (_receiver.IsKeyDown(irr::KEY_KEY_Z) && _y <= 110) {
		_sydney[0]->setRotation(irr::core::vector3df(-180, 0, 180));
		actions.first = 2;
	} else if (_receiver.IsKeyDown(irr::KEY_KEY_S) && _y >= 10) {
		_sydney[0]->setRotation(irr::core::vector3df(-180, 0, 0));
		actions.first = 1;
	}
	if (_receiver.IsKeyDown(irr::KEY_KEY_D) && _x <= 150) {
		_sydney[0]->setRotation(irr::core::vector3df(-180, 0, 90));
		actions.first = 4;
	} else if (_receiver.IsKeyDown(irr::KEY_KEY_Q) && _x >= 10) {
		_sydney[0]->setRotation(irr::core::vector3df(-180, 0, -90));
		actions.first = 3;
	}
	if (_receiver.IsKeyDown(irr::KEY_KEY_E)) {
		actions.first = 6;
	}
	if (_receiver.IsKeyDown(irr::KEY_KEY_O) && _y <= 110) {
		_sydney[1]->setRotation(irr::core::vector3df(-180, 0, 180));
		actions.second = 2;
	} else if (_receiver.IsKeyDown(irr::KEY_KEY_L) && _y >= 10) {
		_sydney[1]->setRotation(irr::core::vector3df(-180, 0, 0));
		actions.second = 1;
	}
	if (_receiver.IsKeyDown(irr::KEY_KEY_M) && _x <= 150) {
		_sydney[1]->setRotation(irr::core::vector3df(-180, 0, 90));
		actions.second = 4;
	} else if (_receiver.IsKeyDown(irr::KEY_KEY_K) && _x >= 10) {
		_sydney[1]->setRotation(irr::core::vector3df(-180, 0, -90));
		actions.second = 3;
	}
	if (_receiver.IsKeyDown(irr::KEY_KEY_P)) {
		actions.second = 6;
	}
	if (_receiver.IsKeyDown(irr::KEY_RETURN)) {
		if (_over)
			_rtomenu = true;
	}
	return (actions);
}

bool DisplayGame::gameOver(void)
{
	wchar_t winner[64];
	
	_over = true;
	_driver->draw2DImage(_tgover, irr::core::position2d<irr::s32>(0, 0),
			     irr::core::rect<irr::s32>(0, 0, 1920, 1080), 0,
			     irr::video::SColor(255, 255, 255, 255), true);
	swprintf(winner, 64, L"PLayer %i won !\n", _game.won());
	_font->draw(winner, irr::core::rect<irr::s32>(840, 250, 200, 200)
			    , irr::video::SColor(255, 51, 153 , 255));
}

void DisplayGame::quit(void)
{
	_device->closeDevice();
	_device->drop();
}

bool DisplayGame::handleAll(void)
{
	bool rt = false;

	_device->getCursorControl()->setVisible(false);
	setScreen();
	setModel();
	if (_config.state == LOADGAME)
		_game.load_save();
	else
		_game.create_map(_config);
	loadTextures();
	addFloor();
	buildMap(_game.get_map());
	while (_device->run()) {
		_driver->beginScene(true, true, irr::video::SColor(255, 0, 0, 0));
		updateMap(_game.get_map());
		buildPlayer(_game.get_players(), _game.get_nb_all());
		displayScore();
		displayKeys();
		if (!_game.play(eventHandler())) {
			gameOver();
			if (_rtomenu) {
				rt = true;
				break;
			}
		} else
			_sceneMgr->drawAll();
		_driver->endScene();
		_powerups.clear();
	}
	return rt;
}

void DisplayGame::loadTextures(void)
{
	int i = 0;

	_tblock = _driver->getTexture(BLOCK_PATH);
	_tfloor = _driver->getTexture(GRASS_PATH);
	_tbreak = _driver->getTexture(CRATE_PATH);
	_tbombup = _driver->getTexture(BOMB_UP);
	_tfireup = _driver->getTexture(FIRE_UP);
	_tspeedup = _driver->getTexture(SPEED_UP);
	_tfire = _driver->getTexture(FIRE_PATH);
	_tgover = _driver->getTexture(GOVER_PATH);
	_tkeyP1 = _driver->getTexture(KEYP1_PATH);
	_tkeyP2 = _driver->getTexture(KEYP2_PATH);
	_tesc = _driver->getTexture(ESC_PATH);
	while (i != _game.get_nb_all()) {
	_sydney.push_back(
		_sceneMgr->addAnimatedMeshSceneNode(_sceneMgr->getMesh(BMAN3D_PATH)));
	i++;
	}
}

void DisplayGame::addFloor(void)
{
	irr::core::dimension2d<irr::f32> tileSize(10.0,10.0);
	irr::core::dimension2d<irr::u32> tileCount(17,13);
	_material = new irr::video::SMaterial();
	_material->setTexture(0, _tfloor);
	irr::f32 hillHeight = 0;
	irr::core::dimension2d<irr::f32> countHills(20.0,20.0);
	irr::core::dimension2d<irr::f32> textureRepeatCount(10.0,10.0);
	irr::scene::IMesh *mesh =_sceneMgr->getGeometryCreator()->createHillPlaneMesh(
		tileSize,
		tileCount,
		_material,
		hillHeight,
		countHills,
		textureRepeatCount);
	mesh->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	_floor = _sceneMgr->addMeshSceneNode(mesh);
	_floor->setPosition(irr::core::vector3df(80.0f, 60.0f, 5.0f));
	_floor->setRotation(irr::core::vector3df(-90, 0, 0));
}

void DisplayGame::displayScore(void)
{
	std::vector<int> scores = _game.getScores();
	wchar_t tmp[1024];
	int i = 0;

	while (i != scores.size()) {
		swprintf(tmp, 1024, L"%s PLayer %i : %i\n", tmp, i + 1, scores[i]);
		_font->draw(L"Score: \n", irr::core::rect<irr::s32>(10, 60, 200, 200)
				    , irr::video::SColor(255, 0, 0 , 255));
		switch (i) {
		case 0:
			_font->draw(tmp, irr::core::rect<irr::s32>(10, 100, 200, 200)
				    , irr::video::SColor(255, 0, 255 , 255));
			break;
		case 1:
			_font->draw(tmp, irr::core::rect<irr::s32>(10, 140, 200, 200)
				    , irr::video::SColor(255, 255, 0 , 255));
			break;
		case 2:
			_font->draw(tmp, irr::core::rect<irr::s32>(10, 180, 200, 200)
				    , irr::video::SColor(255, 255, 0 , 0));
			break;
		case 3:
			_font->draw(tmp, irr::core::rect<irr::s32>(10, 220, 200, 200)
				    , irr::video::SColor(255, 0, 155 , 255));
			break;
		}
		i++;
	}
}

void DisplayGame::displayKeys(void)
{
	_driver->draw2DImage(_tkeyP1, irr::core::position2d<irr::s32>(50, 800),
			     irr::core::rect<irr::s32>(0, 0, 274, 182), 0,
			     irr::video::SColor(255, 255, 255, 255), true);
	_driver->draw2DImage(_tkeyP2, irr::core::position2d<irr::s32>(1600, 800),
			     irr::core::rect<irr::s32>(0, 0, 274, 182), 0,
			     irr::video::SColor(255, 255, 255, 255), true);
	_driver->draw2DImage(_tesc, irr::core::position2d<irr::s32>(1600, 70),
			     irr::core::rect<irr::s32>(0, 0, 300, 100), 0,
			     irr::video::SColor(255, 255, 255, 255), true);
}
