//
// EPITECH PROJECT, 2018
// indie_studio
// File description:
// Build game functions for DisplayerGame
//

#include "DisplayGame.hpp"

void DisplayGame::buildPowerup(int id, float x, float y , tiletype type)
{
	irr::core::vector3df vec(x * IRR_SIZE, y * IRR_SIZE, 2.5);

	_powerups.push_back(_sceneMgr->addCubeSceneNode(5.0f, 0, -1, vec));
	_powerups[id]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	setTexture(id, type);
}

void DisplayGame::buildBlock(int id, float x, float y, tiletype type)
{
	irr::core::vector3df vec(x * IRR_SIZE, y * IRR_SIZE, 0);

	_cubes.push_back(_sceneMgr->addCubeSceneNode(10.0f, 0, -1, vec));
	_cubes[id]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	setTexture(id, type);
}

void DisplayGame::buildBomb(int id, float x, float y, tiletype type)
{
	_bombs.push_back(_sceneMgr->
			 addMeshSceneNode(_sceneMgr->getMesh(BOMB3D_PATH)));
	_bombs[id]->setMaterialTexture(0, _driver->getTexture(BOMBTEX_PATH));
	_bombs[id]->setScale(irr::core::vector3df(20.0f, 20.0f, 20.0f));
	_bombs[id]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	_bombs[id]->setPosition(irr::core::vector3df(x * IRR_SIZE, y * IRR_SIZE, 3));
}

void DisplayGame::buildPlayer(std::vector<player> player, int nb_players)
{
	for (int i = 0; i != nb_players; i++) {
		_sydney[i]->setScale(irr::core::vector3df(0.05f, 0.05f, 0.05f));
		_sydney[i]->setMaterialTexture(0, _driver->getTexture(BMANTEX_PATH));
		_sydney[i]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	       	_sydney[i]->setRotation(irr::core::vector3df(-180, 0, 0));
		_sydney[i]->setPosition(irr::core::vector3df
					((player[i].get_x() - 0.5) * IRR_SIZE
					 , (player[i].get_y() - 0.5) * IRR_SIZE + 2, 5));
	}
}

void DisplayGame::setTexture(int id, tiletype type)
{
	switch (type) {
	case EMPTY:
		_cubes[id]->setVisible(false);
	case BLOCK:
		_cubes[id]->setMaterialTexture(0, _tblock);
		break;
	case BREAKABLE:
		_cubes[id]->setMaterialTexture(0, _tbreak);
		break;
	case FLAME:
		_cubes[id]->setMaterialTexture(0, _tfire);
		break;
	case POWERUP_BOMB:
		_powerups[id]->setMaterialTexture(0, _tbombup);
		break;
	case POWERUP_RANGE:
		_powerups[id]->setMaterialTexture(0, _tfireup);
		break;
	case POWERUP_SPEED:
		_powerups[id]->setMaterialTexture(0, _tspeedup);
		break;
	default:
		break;
	}
}

void DisplayGame::updateTexture(int id, tiletype type)
{
	switch (type) {
	case EMPTY:
		_cubes[id]->setVisible(false);
	case BLOCK:
		_cubes[id]->setMaterialTexture(0, _tblock);
		break;
	case BREAKABLE:
		_cubes[id]->setMaterialTexture(0, _tbreak);
		break;
	case FLAME:
		if (!_cubes[id]->isVisible())
			_cubes[id]->setVisible(true);
		_cubes[id]->setMaterialTexture(0, _tfire);
		break;
	case POWERUP_BOMB:
		_powerups[id]->setMaterialTexture(0, _tbombup);
		break;
	case POWERUP_RANGE:
		_powerups[id]->setMaterialTexture(0, _tfireup);
		break;
	case POWERUP_SPEED:
		_powerups[id]->setMaterialTexture(0, _tspeedup);
		break;
	default:
		break;
	}
}

void DisplayGame::updateMap(std::vector<std::vector<items>> map)
{
	int type = 0;
	int b = 0;
	int p = 0;
	int nb_bomb = 0;

	for (float y = 0; y < SIZE_MAP_Y; y++) {
		for (float x = 0; x < SIZE_MAP_X; x++) {
			type = map[y][x].get_id();
			if (type < 4) {
				updateTexture(b, (tiletype)type);
			} else if (type == BOMB) {
				updateTexture(b, EMPTY);
				buildBomb(nb_bomb, x, y, (tiletype)type);
				nb_bomb++;
			} else {
				updateTexture(b, EMPTY);
				buildPowerup(p, x, y, (tiletype)type);
				p++;
			}
			b++;
		}
	}
}

void DisplayGame::buildMap(std::vector<std::vector<items>> map)
{
	int type = 0;
	int b = 0;

	for (float y = 0; y < SIZE_MAP_Y; y++) {
		for (float x = 0; x < SIZE_MAP_X; x++) {
			type = map[y][x].get_id();
			if (type < 4) {
				buildBlock(b, x, y, (tiletype)type);
			} else {
				buildBlock(b, x, y, EMPTY);
			}
			b++;
		}
	}
}
