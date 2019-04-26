//
// EPITECH PROJECT, 2018
// player
// File description:
// player
//

#include "player.hpp"

player::player()
{
}

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
	_score = 0;
	_dirCheck = false;
	dir = 0;
}

player::~player()
{
}

bool player::is_alive()
{
	return _alive;
}

int player::get_num()
{
	return _num;
}

bool player::check_bonus()
{
	return _bonus;
}

void player::speed_up()
{
	++_bonus_speed;
	_speed += (0.02 * _bonus_speed);
	_bonus = true;
}

void player::speed_down()
{
	--_speed;
	if (_speed < 0)
		_speed = 1;
}

void player::range_up()
{
	_bonus = true;
	++_range;
}

void player::range_down()
{
	--_range;
	if (_range == 0)
		++_range;
}

void player::boom_up()
{
	_bonus = true;
	++_nb_bomb;
}

void player::boom_down()
{
	--_nb_bomb;
	if (_nb_bomb == 0)
		++_nb_bomb;
}

void player::add_bonus(std::vector<std::vector<items>> map)
{
	int id = map[_y][_x].get_id();

	switch (id) {
	case EMPTY:
		_bonus = false;
		break;
	case FLAME:
		_bonus = false;
		_alive = false;
		break;
	case POWERUP_SPEED:
		_smgr.playSound(POWUP);
		_score += 10;
		speed_up();
		break;
	case POWERUP_RANGE:
		_smgr.playSound(POWUP);
		_score += 10;
		range_up();
		break;
	case POWERUP_BOMB:
		_smgr.playSound(POWUP);
		_score += 10;
		boom_up();
		break;
	}
	return;
}

int player::getScore()
{
	return _score;
}

bomb player::create_bomb(int x, int y, int team, int range)
{
	bomb bomb(x, y, team, range);
	return bomb;
}

bool player::put_bomb(std::vector<std::vector<items>> map,
		      std::list<bomb> bomb)
{
	int id = map[_y][_x].get_id();
	unsigned int tpm = 0;

	for (auto &the_bomb : bomb) {
		if (the_bomb.get_team() == _num)
			++tpm;
	}
	if (id != BOMB && tpm < _nb_bomb) {
		_new_bomb.clear();
		_new_bomb.push_back(create_bomb(_x, _y, _num, _range));
		return true;
	}
	return false;
}

std::vector<bomb> player::get_bomb()
{
	return _new_bomb;
}

bool player::player_turn(std::vector<std::vector<items>> map,
			 int action, std::list<bomb> bomb)
{
	add_bonus(map);
	switch (action)
	{
	case UP:
		player_up(map);
		break;;
	case DOWN:
		player_down(map);
		break;
	case LEFT:
		player_left(map);
		break;
	case RIGHT:
		player_right(map);
		break;
	case PUT_BOMB:
		return put_bomb(map, bomb);
	}
	return false;
}

void player::player_up(std::vector<std::vector<items>> map)
{
	int next_pos = floor(_y - _speed - HIT);
	int id = map[next_pos][_x].get_id();

	if (id == map[_y][_x].get_id() && next_pos == (int)_y)
		_y -= _speed;
	else if (_y - _speed - 1 - HIT > 0 &&
		 id != BREAKABLE &&
		 id != BLOCK &&
		 id != BOMB)
		_y -= _speed;
}

void player::player_down(std::vector<std::vector<items>> map)
{
	int next_pos = floor(_y + _speed + HIT);
	int id = map[next_pos][_x].get_id();

	if (id == map[_y][_x].get_id() && next_pos < _y)
		_y += _speed;
	else if (id != BREAKABLE &&
		 id != BLOCK &&
		 id != BOMB)
		_y += _speed;
}

void player::player_left(std::vector<std::vector<items>> map)
{
	int next_pos = floor(_x - _speed - HIT);
	int id = map[_y][next_pos].get_id();

	if (id == map[_y][_x].get_id() && next_pos == (int) _x)
		_x -= _speed;
	else if (id != BREAKABLE &&
		 id != BLOCK &&
		 id != BOMB)
		_x -= _speed;
}

void player::player_right(std::vector<std::vector<items>> map)
{
	int next_pos = floor(_x + _speed + HIT);
	int id = map[_y][next_pos].get_id();

	if (id == map[_y][_x].get_id() && next_pos < _x)
		_x += _speed;
	else if  (id != BREAKABLE &&
		  id != BLOCK &&
		  id != BOMB)
		_x += _speed;
}

float player::get_x()
{
	return _x;
}

float player::get_y()
{
	return _y;
}

bool player::is_bot()
{
	return _bot;
}

bool player::bot_turn(std::vector<std::vector<items>> map,
	std::list<bomb> bombs)
{
	bool	ret_bomb = false;

	add_bonus(map);
	get_danger_map(bombs, map);
	if (_danger_map[floor(_y)][floor(_x)] == 0){
		if (is_safe_to_bomb(map) == true) {
			if (map[floor(_y) + 1][floor(_x)].get_id() == 2 ||
			map[floor(_y) - 1][floor(_x)].get_id() == 2 ||
			map[floor(_y)][floor(_x) + 1].get_id() == 2 ||
			map[floor(_y)][floor(_x) - 1].get_id() == 2) {
				ret_bomb = put_bomb(map, bombs);
				return ret_bomb;
			} else
			bot_movement(map);
		} else
		bot_movement(map);
	}
	else if (_danger_map[floor(_y)][floor(_x)] == 1)
	if (quick_check_around(map) != true)
	escape(map);
	return false;
}


void player::save(std::fstream &file)
{
	file << _bot << " " <<_x << " " << _y << " " << _num <<
		" " << _bonus_speed << " " << _nb_bomb << " "
	     << _range <<" " << _score << ";";
}

void player::get_save()
{
	_speed = 0.17;
	_bonus_speed = atoi(strtok(NULL, " \n;"));
	_bonus = false;
	_nb_bomb = atoi(strtok(NULL, " \n;"));
	_range = atoi(strtok(NULL, " \n;"));
	_score = atoi(strtok(NULL, " \n;"));
}

bool player::getCheckDir(void)
{
	return (_dirCheck);
}

void player::setCheckDir(bool checked)
{
	_dirCheck = checked;
}
