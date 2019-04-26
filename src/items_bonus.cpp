//
// EPITECH PROJECT, 2018
// bonus
// File description:
// bnus
//

#include "items_bonus.hpp"

bonus::bonus()
{
	int tpm = 0;

	tpm = rand() % 6;
	switch (tpm) {
	case 0:
		_id = POWERUP_SPEED;
		break;
	case 1:
		_id = POWERUP_RANGE;
		break;
	case 2:
		_id = POWERUP_BOMB;
		break;
	case 3:
		_id = EMPTY;
		break;
	case 4:
		_id = EMPTY;
		break;
	case 5:
		_id = EMPTY;
		break;
	}
}

bonus::~bonus()
{
}
