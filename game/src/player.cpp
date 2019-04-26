//
// EPITECH PROJECT, 2018
// player
// File description:
// player
//

#include "player.hpp"

player::player(bool is_bot, float x, float y, int num)
{
	_bot = is_bot;
	_x = x;
	_y = y;
	_num = num;
	_nb_bomb = 1;
	_range = 2;
	_speed = 0.17;
	_alive = true;
	_bonus_speed = 0;
}

player::~player()
{
}

bool	player::is_alive()
{
	return _alive;
}

int	player::get_num()
{
	return _num;
}

bool	player::check_bonus()
{
	return _bonus;
}

void	player::speed_up()
{
//	++_bonus_speed;
//	_speed += (0.05 * _bonus_speed);
	_bonus = true;
}

void	player::speed_down()
{
	--_speed;
	if (_speed < 0)
		_speed = 1;
}

void		player::range_up()
{
	_bonus = true;
	++_range;
}

void	player::range_down()
{
	--_range;
	if (_range == 0)
		++_range;
}

void		player::boom_up()
{
	_bonus = true;
	++_nb_bomb;
}

void	player::boom_down()
{
	--_nb_bomb;
	if (_nb_bomb == 0)
		++_nb_bomb;
}

void		player::add_bonus(std::vector<std::vector<items>> map)
{
	int	id = map[_y][_x].get_id();

	std::cout << id << std::endl;
	switch (id) {
	case EMPTY:
		_bonus = false;
		return;
	case FLAME:
		_bonus = false;
		_alive = false;
		return;
	case POWERUP_SPEED:
		speed_up();
		return;
	case POWERUP_RANGE:
		range_up();
		return;
	case POWERUP_BOMB:
		boom_up();
		return;
	}
	return;
}

bool		player::put_bomb(std::vector<std::vector<items>> map)
{
	int	id = map[_y][_x].get_id();
	bomb	new_bomb(_x, _y, 1, _range);

	if (id != BOMB) {
		_new_bomb.clear();
		_new_bomb.push_back(new_bomb);
		return true;
	}
	return false;
}

std::vector<bomb>	player::get_bomb()
{
	return _new_bomb;
}

bool	player::player_turn(std::vector<std::vector<items>> map, int action)
{
	add_bonus(map);
	switch (action)
	{
	case UP:
		player_up(map);
		return false;
	case DOWN:
		player_down(map);
		return false;
	case LEFT:
		player_left(map);
		return false;
	case RIGHT:
		player_right(map);
		return false;
	case PUT_BOMB:
		return put_bomb(map);
	}
	return false;
}

void		player::player_up(std::vector<std::vector<items>> map)
{
	int	next_pos = floor(_y - _speed - HIT);
	int	id = map[next_pos][_x].get_id();

	if (id == map[_y][_x].get_id() && next_pos == (int)_y)
		_y -= _speed;
	else if (_y - _speed - 1 - HIT > 0 &&
		 id != BREAKABLE &&
		 id != BLOCK &&
		 id != BOMB)
		_y -= _speed;
}

void		player::player_down(std::vector<std::vector<items>> map)
{
	int	next_pos = floor(_y + _speed + HIT);
	int	id = map[next_pos][_x].get_id();

	if (id == map[_y][_x].get_id() && next_pos < _y)
		_y += _speed;
	else if (id != BREAKABLE &&
		 id != BLOCK &&
		 id != BOMB)
		_y += _speed;
}

void		player::player_left(std::vector<std::vector<items>> map)
{
	int	next_pos = floor(_x - _speed - HIT);
	int	id = map[_y][next_pos].get_id();

	if (id == map[_y][_x].get_id() && next_pos == (int) _x)
		_x -= _speed;
	else if (id != BREAKABLE &&
		 id != BLOCK &&
		 id != BOMB)
		_x -= _speed;
}

//	std::cout << "GO LEFT:" << std::endl << "next_pos_x = "
//		  << next_pos << " _x = " << _x << " _y = " << _y << std::endl;

void		player::player_right(std::vector<std::vector<items>> map)
{
	int	next_pos = floor(_x + _speed + HIT);
	int	id = map[_y][next_pos].get_id();

	if (id == map[_y][_x].get_id() && next_pos < _x)
		_x += _speed;
	else if  (id != BREAKABLE &&
		  id != BLOCK &&
		  id != BOMB)
		_x += _speed;
}

float	player::get_x()
{
	return _x;
}

float	player::get_y()
{
	return _y;
}

bool	player::is_bot()
{
	return _bot;
}

bool	player::bot_turn(std::vector<std::vector<items>> map)
{
	(void) map;
	return true;
}
