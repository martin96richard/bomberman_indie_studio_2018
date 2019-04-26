//
// EPITECH PROJECT, 2018
// menu
// File description:
// menu
//

#include "menu.hpp"

Menu::Menu()
{
	_state = INTRO;
	_begintime = std::time(nullptr);
	_device = irr::createDevice(
		irr::video::EDT_OPENGL,
		irr::core::dimension2d<irr::u32>(800, 600),
		32, false, true, false, 0);
	_driver = _device->getVideoDriver();
	_scnMgr = _device->getSceneManager();
	_guiEnv = _device->getGUIEnvironment();
	_engine = irrklang::createIrrKlangDevice();
	_play = false;
	_music = _engine->play2D(MUSIC_PATH, true, false, true,
				 irrklang::ESM_AUTO_DETECT, true);
	_players.nb_P = 1;
	_players.P1 = HUMAN;
	_players.P2 = EMPT;
	_players.P3 = EMPT;
	_players.P4 = EMPT;
}

Menu::~Menu()
{
}

void Menu::setFont(void)
{
	_fontTitle = _guiEnv->getFont(TFONT_PATH);
	_font = _guiEnv->getFont(FONT_PATH);
	_font2 = _guiEnv->getFont(FONT2_PATH);
	_title->setOverrideFont(_fontTitle);
	_sTitlePlayers->setOverrideFont(_font);
	_sTitleMap->setOverrideFont(_font);
	_nbPlayers->setOverrideFont(_font);
	_btnMore->setOverrideFont(_font2);
	_btnMinus->setOverrideFont(_font2);
	_btnP1->setOverrideFont(_font2);
	_btnP2->setOverrideFont(_font2);
	_btnP3->setOverrideFont(_font2);
	_btnP4->setOverrideFont(_font2);
	_btnNgame->setOverrideFont(_font);
	_btnLgame->setOverrideFont(_font);
	_btnSettings->setOverrideFont(_font);
	_btnReturn->setOverrideFont(_font);
	_btnPlay->setOverrideFont(_font);
}

void Menu::setVisibility(void)
{
	_title->setVisible(false);
	_btnNgame->setVisible(false);
	_btnLgame->setVisible(false);
	_btnSettings->setVisible(false);
	
	_btnReturn->setVisible(false);
	_btnPlay->setVisible(false);
	_sTitlePlayers->setVisible(false);
	_sTitleMap->setVisible(false);
	_nbPlayers->setVisible(false);
	_btnMore->setVisible(false);
	_btnMinus->setVisible(false);
	_btnP1->setVisible(false);
	_btnP2->setVisible(false);
	_btnP3->setVisible(false);
	_btnP4->setVisible(false);
}

void Menu::loadTextures(void)
{
	_driver->setTextureCreationFlag(irr::video::ETCF_ALWAYS_32_BIT, true);
	_wallpaper = _driver->getTexture(WALL_PATH);
	_splash = _driver->getTexture(SPLASH_PATH);
	_wall2 = _driver->getTexture(WALL2_PATH);
	_imgSolo = _driver->getTexture(SOLO_PATH);
	_imgDuo = _driver->getTexture(DUO_PATH);
	_imgTrio = _driver->getTexture(TRIO_PATH);
	_imgQuad = _driver->getTexture(QUAD_PATH);
	_imgHuman = _driver->getTexture(HUMAN_PATH);
	_imgIA = _driver->getTexture(IA_PATH);
	_imgEmpty = _driver->getTexture(EMPTY_PATH);
	_imgMap1 = _driver->getTexture(MAP1_PATH);
	_imgMap2 = _driver->getTexture(MAP2_PATH);
	_imgMap3 = _driver->getTexture(MAP3_PATH);
	_imgBtnMore = _driver->getTexture(MORE_PATH);
	_imgBtnMinus = _driver->getTexture(MINUS_PATH);
}

void Menu::setIDs(void)
{
	_btnMore->setID(BTN_MORE);
	_btnMinus->setID(BTN_MINUS);
	_btnP1->setID(BTN_P1);
	_btnP2->setID(BTN_P2);
	_btnP3->setID(BTN_P3);
	_btnP4->setID(BTN_P4);
}

void Menu::addElements(void)
{
	_title = _guiEnv->addStaticText(
		L"", irr::core::rect<irr::s32>(300,50, 550,90), true, true, 0, -1);
	_sTitlePlayers = _guiEnv->addStaticText(
		L"PLAYERS", irr::core::rect<irr::s32>(50, 120, 700, 150), true, true, 0, -1);
	_sTitleMap = _guiEnv->addStaticText(
		L"MAP", irr::core::rect<irr::s32>(50, 320, 700, 350), true, true, 0, -1);
	_nbPlayers = _guiEnv->addStaticText(
		L"Solo", irr::core::rect<irr::s32>(95,160,160,190), true, true, 0, -1);
	_btnNgame = _guiEnv->addButton(
		irr::core::rect<irr::s32>(50, 220, 300, 300), 0, -1, L"New Game");
	_btnLgame  = _guiEnv->addButton(
		irr::core::rect<irr::s32>(50, 320, 300, 400), 0, -1, L"Load Game");
	_btnSettings  = _guiEnv->addButton(
		irr::core::rect<irr::s32>(50, 420, 300, 500), 0, -1, L"Settings");
	_btnPlay  = _guiEnv->addButton(irr::core::rect<irr::s32>(400, 500, 600, 570),
					  0, -1, L"Play");
	_btnReturn = _guiEnv->addButton(irr::core::rect<irr::s32>(190, 500, 390, 570),
					  0, -1, L"Menu");
	_btnMore = _guiEnv->addButton(irr::core::rect<irr::s32>(250, 210, 280, 240),
					  0, -1, L"+");
	_btnMinus = _guiEnv->addButton(irr::core::rect<irr::s32>(250, 250, 280, 280),
					  0, -1, L"-");
	_btnP1 = _guiEnv->addButton(irr::core::rect<irr::s32>(310, 285, 370, 310),
					  0, -1, L"switch");
	_btnP2 = _guiEnv->addButton(irr::core::rect<irr::s32>(420, 285, 480, 310),
					  0, -1, L"switch");
	_btnP3 = _guiEnv->addButton(irr::core::rect<irr::s32>(530, 285, 590, 310),
					  0, -1, L"switch");
	_btnP4 = _guiEnv->addButton(irr::core::rect<irr::s32>(640, 285, 700, 310),
					  0, -1, L"switch");
}

void Menu::drawNGame(void)
{
	_driver->draw2DImage(_wall2, irr::core::position2d<irr::s32>(0, 0),
			     irr::core::rect<irr::s32>(0, 0, 800, 600), 0,
			     irr::video::SColor(255, 255, 255, 255), true);
	_driver->draw2DImage(getImgForNBPlayers(),
			     irr::core::position2d<irr::s32>(80, 200),
			     irr::core::rect<irr::s32>(0, 0, 100, 100), 0,
			     irr::video::SColor(255, 255, 255, 255), true);
	_driver->draw2DImage(getPlayerSkin(1),
			     irr::core::position2d<irr::s32>(300, 180),
			     irr::core::rect<irr::s32>(0, 0, 80, 100), 0,
			     irr::video::SColor(255, 255, 255, 255), true);
	_driver->draw2DImage(getPlayerSkin(2),
			     irr::core::position2d<irr::s32>(410, 180),
			     irr::core::rect<irr::s32>(0, 0, 80, 100), 0,
			     irr::video::SColor(255, 255, 255, 255), true);
	_driver->draw2DImage(getPlayerSkin(3),
			     irr::core::position2d<irr::s32>(520, 180),
			     irr::core::rect<irr::s32>(0, 0, 80, 100), 0,
			     irr::video::SColor(255, 255, 255, 255), true);
	_driver->draw2DImage(getPlayerSkin(4),
			     irr::core::position2d<irr::s32>(630, 180),
			     irr::core::rect<irr::s32>(0, 0, 80, 100), 0,
			     irr::video::SColor(255, 255, 255, 255), true);
	_driver->draw2DImage(_imgMap1,
			     irr::core::position2d<irr::s32>(300, 360),
			     irr::core::rect<irr::s32>(0, 0, 180, 110), 0,
			     irr::video::SColor(255, 255, 255, 255), true);
}

void Menu::drawImages(void)
{
	if (_state == NEWGAME) {
		drawNGame();
	} else if (_state == INTRO) {
		_driver->draw2DImage(_splash, irr::core::position2d<irr::s32>(0, 0),
				     irr::core::rect<irr::s32>(0, 0, 800, 600), 0,
				     irr::video::SColor(255, 255, 255, 255), true);
		if (difftime(std::time(nullptr), _begintime) > 8)
			_state = MENU;
	} else {
		_driver->draw2DImage(_wallpaper, irr::core::position2d<irr::s32>(0, 0),
				     irr::core::rect<irr::s32>(0, 0, 800, 600), 0,
				     irr::video::SColor(255, 255, 255, 255), true);
	}
}

irr::video::ITexture* Menu::getImgForNBPlayers(void)
{
	if (_players.nb_P == 1)
		return _imgSolo;
	if (_players.nb_P == 2)
		return _imgDuo;
	if (_players.nb_P == 3)
		return _imgTrio;
	if (_players.nb_P == 4)
		return _imgQuad;
}

irr::video::ITexture* Menu::getPlayerSkin(int np)
{
	switch (np) {
	case 1:
		if (_players.P1 == EMPT)
			return _imgEmpty;
		else if (_players.P1 == HUMAN)
			return _imgHuman;
		else
			return _imgIA;
	case 2:
		if (_players.P2 == EMPT)
			return _imgEmpty;
		else if (_players.P2 == HUMAN)
			return _imgHuman;
		else
			return _imgIA;
	case 3:
		if (_players.P3 == EMPT)
			return _imgEmpty;
		else if (_players.P3 == HUMAN)
			return _imgHuman;
		else
			return _imgIA;
	case 4:
		if (_players.P4 == EMPT)
			return _imgEmpty;
		else if (_players.P4 == HUMAN)
			return _imgHuman;
		else
			return _imgIA;
	}
}

Players Menu::getPlayers(void)
{
	return _players;
}

void Menu::setPlayers(Players players)
{
	_players = players;
}

bool Menu::checkButtons(void)
{
	if (_btnNgame->isPressed()) {
		_state = NEWGAME;
		return true;
	}
	if (_btnLgame->isPressed()) {
		_state = LOADGAME;
		_play = true;
		return true;
	}
	if (_btnSettings->isPressed()) {
		_state = SETTINGS;
		return true;
	}
	if (_btnReturn->isPressed()) {
		_state = MENU;
		return true;
	}
	if (_btnPlay->isPressed()) {
		_play = true;
		return true;
	}
	return false;
}

void Menu::setToMenu(void)
{
	_title->setVisible(false);
	_btnNgame->setVisible(true);
	_btnLgame->setVisible(true);
	_btnSettings->setVisible(true);

	_btnReturn->setVisible(false);
	_btnPlay->setVisible(false);
	_sTitlePlayers->setVisible(false);
	_sTitleMap->setVisible(false);
	_nbPlayers->setVisible(false);
	_btnMore->setVisible(false);
	_btnMinus->setVisible(false);
	_btnP1->setVisible(false);
	_btnP2->setVisible(false);
	_btnP3->setVisible(false);
	_btnP4->setVisible(false);
}

void Menu::setToIntro(void)
{
	_title->setVisible(false);
	_btnNgame->setVisible(false);
	_btnLgame->setVisible(false);
	_btnSettings->setVisible(false);
}

void Menu::setToNGame(void)
{
	_title->setText(L"New Game");
	_title->setVisible(true);
	_btnNgame->setVisible(false);
	_btnLgame->setVisible(false);
	_btnSettings->setVisible(false);

	_btnReturn->setVisible(true);
	_btnPlay->setVisible(true);
	_sTitlePlayers->setVisible(true);
	_sTitleMap->setVisible(true);
	_nbPlayers->setVisible(true);
	_btnMore->setVisible(true);
	_btnMinus->setVisible(true);
	_btnP1->setVisible(true);
	_btnP2->setVisible(true);
	_btnP3->setVisible(true);
	_btnP4->setVisible(true);
	switch (_players.nb_P) {
	case 1:
		_nbPlayers->setText(L"Solo");
		break;
	case 2:
		_nbPlayers->setText(L"Duo");
		break;
	case 3:
		_nbPlayers->setText(L"Trio");
		break;
	case 4:
		_nbPlayers->setText(L"Quad");
		break;
	}
}

void Menu::updateGUI(void)
{
	switch (_state) {
	case INTRO:
		setToIntro();
		break;
	case MENU:
		setToMenu();
		break;
	case NEWGAME:
		setToNGame();
		break;
	default:
		break;
	}
}

irrklang::ISoundEngine* Menu::getEngine(void)
{
	return _engine;
}

void Menu::initMenu(void)
{
	addElements();
	loadTextures();
	setIDs();
	setFont();
	setVisibility();
}

bool Menu::runMenu(void)
{
	initMenu();
	MenuEventReceiver receiver(getPlayers());
	_device->setEventReceiver(&receiver);
	receiver.setEngine(_engine);
	while (_device->run()) {
		_driver->beginScene(true, true, irr::video::SColor(0,192,192,192));
		drawImages();
		setPlayers(receiver.updatePlayers());
		checkButtons();
		updateGUI();
		_guiEnv->drawAll();
		_scnMgr->drawAll();
		_driver->endScene();
		if (_play) {
			_music->drop();
			_engine->drop();
			_device->drop();
			return true;
		}
	}
	_music->drop();
	_engine->drop();
	_device->drop();
	return false;
}

GameConfig Menu::getGameConfig(void)
{
	GameConfig config;

	config.state = _state;
	config.players = &_players;

	return (config);
}
