//
// EPITECH PROJECT, 2018
// event
// File description:
// event receiver
//

#include "event.hpp"

MenuEventReceiver::MenuEventReceiver(Players players)
{
	_players = players;
}

void MenuEventReceiver::playSound(void)
{
	_clic = _engine->play2D(CLIC_PATH, false, false, true, irrklang::ESM_AUTO_DETECT,
				false);
}

void MenuEventReceiver::addPlayer(void)
{
	if (_players.nb_P < 4)
		_players.nb_P += 1;
	switch (_players.nb_P) {
	case 2:
		_players.P2 = HUMAN;
		break;
	case 3:
		_players.P3 = HUMAN;
		break;
	case 4:
		_players.P4 = HUMAN;
		break;
	}
}

void MenuEventReceiver::delPlayer(void)
{
	if (_players.nb_P > 1)
		_players.nb_P -= 1;
	switch (_players.nb_P) {
	case 1:
		_players.P2 = EMPT;
		break;
	case 2:
		_players.P3 = EMPT;
		break;
	case 3:
		_players.P4 = EMPT;
		break;
	}
}

void MenuEventReceiver::switchState(int np)
{
	switch (np) {
	case 1:
		if (_players.P1 == HUMAN)
			_players.P1 = IA;
		else if (_players.P1 == IA)
			_players.P1 = HUMAN;
		break;
	case 2:
		if (_players.P2 == HUMAN)
			_players.P2 = IA;
		else if (_players.P2 == IA)
			_players.P2 = HUMAN;
		break;
	case 3:
		if (_players.P3 == HUMAN)
			_players.P3 = IA;
		else if (_players.P3 == IA)
			_players.P3 = HUMAN;
		break;
	case 4:
		if (_players.P4 == HUMAN)
			_players.P4 = IA;
		else if (_players.P4 == IA)
			_players.P4 = HUMAN;
		break;
	}
}

bool MenuEventReceiver::OnEvent(const irr::SEvent &event)
{
	if (event.EventType == irr::EET_GUI_EVENT &&
	    event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED) {
		irr::s32 id = event.GUIEvent.Caller->getID();
		playSound();
		switch (id) {
		case BTN_MORE:
			addPlayer();
			return true;
		case BTN_MINUS:
			delPlayer();
			return true;
		case BTN_P1:
			switchState(1);
			return true;
		case BTN_P2:
			switchState(2);
			return true;
		case BTN_P3:
			switchState(3);
			return true;
		case BTN_P4:
			switchState(4);
			return true;
		}
	}
	return false;
}

void MenuEventReceiver::setEngine(irrklang::ISoundEngine *engine)
{
	_engine = engine;
}

Players MenuEventReceiver::updatePlayers(void)
{
	return _players;
}
