//
// EPITECH PROJECT, 2018
// boom
// File description:
// boom
//

#include "boom.hpp"

bomb::bomb(int x, int y, int team, int range)
{
	_range = range;
	_x = x;
	_y = y;
	_team = team;
	_life = 20;
	_range = range;
	_item = false;
	_id = BOMB;
	_dead = false;
	_type = 0;
	_new = true;
}

void	bomb::wall_crush()
{
	_item = true;
}

bomb::~bomb()
{	
}

void	bomb::set_dead()
{
	_dead = true;
}

bool	bomb::is_dead()
{
	return _dead;
}

int	bomb::get_range()
{
	return _range;
}

void	bomb::set_life()
{
	_life = 0;
}

bool	bomb::cycle()
{
	--_life;
	if (_life <= 0)
		return true;
	return false;
}

flame::flame()
{
	_id = FLAME;
	_items = false;
	_life = 10;
	_dead = false;
}

flame::~flame()
{
}

bool	flame::cycle()
{
	--_life;
	if (_life < 0) {
		_dead = true;
		return true;
	}
	return false;
}

bool	flame::is_dead()
{
	return _dead;
}

void	flame::set_items(bool items)
{
	_items = items;
}

bool	flame::get_items()
{
	return _items;
}
