/*
** EPITECH PROJECT, 2018
** bot
** File description:
** bot
*/

#include "game.hpp"

static std::vector<std::vector<int>>		init_map()
{
	std::vector<std::vector<int>>	danger_map;
	std::vector<int>				tmp;
	int							x = 0;
	int							y = 0;

	while (y < SIZE_MAP_Y) {
		while (x < SIZE_MAP_X) {
			tmp.push_back(0);
			++x;
		}
		danger_map.push_back(tmp);
		tmp.clear();
		x = 0;
		++y;
	}
	return danger_map;
}

int		get_bomb_range(std::list<bomb> bombs, int x, int y)
{
	auto	it = bombs.begin();

	while (it != bombs.end()) {
		if (it->get_x() == x && it->get_y() == y)
			return it->get_range();
		++it;
	}
	return 0;
}

void	player::set_range_on_map(std::vector<std::vector<items>> map,
		int range, int x, int y)
{
	int		i = 1;
	bool	left = true;
	bool	right = true;
	bool	up = true;
	bool	down = true;

	while (i < range) {
		if ((x + i) < SIZE_MAP_X &&
		map[y][x + i].get_id() != 1 && map[y][x + i].get_id() != 2 &&
		right == true)
			_danger_map[y][x + i] = 1;
		else
			right = false;
		if ((x - i) >= 0 &&
		map[y][x - i].get_id() != 1 && map[y][x - i].get_id() != 2 &&
		left == true)
			_danger_map[y][x - i] = 1;
		else
			left = false;
		if ((y + i) < SIZE_MAP_Y &&
		map[y + i][x].get_id() != 1 && map[y + i][x].get_id() != 2 &&
		down == true)
			_danger_map[y + i][x] = 1;
		else
			down = false;
		if ((y - i) >= 0 &&
		map[y - i][x].get_id() != 1 && map[y - i][x].get_id() != 2 &&
		up == true)
			_danger_map[y - i][x] = 1;
		else
			up = false;
		++i;
	}
}

void		player::get_danger_map(std::list<bomb> bombs,
			std::vector<std::vector<items>> map)
{
	int							x = 0;
	int							y = 0;
	int							range = 0;

	_danger_map = init_map();
	while (y < SIZE_MAP_Y) {
		while (x < SIZE_MAP_X) {
			if (map[y][x].get_id() == BOMB) {
				_danger_map[y][x] = 1;
				range = get_bomb_range(bombs, x, y);
				set_range_on_map(map, range, x, y);
			}
			else if (map[y][x].get_id() == FLAME)
				_danger_map[y][x] = 2;
			++x;
		}
		x = 0;
		++y;
	}
}

int		player::check_left(std::vector<std::vector<items>> map)
{
	int		nbr_case = 1;
	int		tx = floor(_x);
	int		ty = floor(_y);
	bool	safe = false;

	if ((tx - 1) > 0 &&
	(map[ty][tx - 1].get_id() != 1 &&
	map[ty][tx - 1].get_id() != 2))
		tx = tx - 1;
	else
		return -1;
	while (safe == false) {
		if ((ty + 1) < SIZE_MAP_Y && map[ty + 1][tx].get_id() != 1 &&
		map[ty + 1][tx].get_id() != 2 && _danger_map[ty + 1][tx] == 0)
			safe = true;
		else if ((ty - 1) >= 0 && map[ty - 1][tx].get_id() != 1 &&
		map[ty - 1][tx].get_id() != 2 && _danger_map[ty - 1][tx] == 0)
			safe = true;
		else if ((tx - 1) >= 0 && map[ty][tx - 1].get_id() != 1 &&
		map[ty][tx - 1].get_id() != 2 && _danger_map[ty][tx - 1] == 0 &&
		(floor(_x) - tx) > (_range - 1))
			safe = true;
		else if ((tx - 1) >= 0 && map[ty][tx - 1].get_id() != 1 &&
		map[ty][tx - 1].get_id() != 2 && _danger_map[ty][tx - 1] == 0 &&
		(floor(_x) - tx) <= (_range - 1))
			tx = tx - 1;
		else
			return -1;
		++nbr_case;
	}
	return nbr_case;
}

int		player::check_right(std::vector<std::vector<items>> map)
{
	int		nbr_case = 1;
	int		tx = floor(_x);
	int		ty = floor(_y);
	bool	safe = false;

	if ((tx + 1) < SIZE_MAP_X &&
	(map[ty][tx + 1].get_id() != 1 &&
	map[ty][tx + 1].get_id() != 2))
		tx = tx + 1;
	else
		return -1;
	while (safe == false) {
		if ((ty + 1) < SIZE_MAP_Y && map[ty + 1][tx].get_id() != 1 &&
		map[ty + 1][tx].get_id() != 2 && map[ty + 1][tx].get_id() != 3 &&
		_danger_map[ty + 1][tx] == 0)
			safe = true;
		else if ((ty - 1) >= 0 && map[ty - 1][tx].get_id() != 1 &&
		map[ty - 1][tx].get_id() != 2 && map[ty - 1][tx].get_id() != 3 &&
		_danger_map[ty - 1][tx] == 0)
			safe = true;
		else if ((tx + 1) < SIZE_MAP_X && map[ty][tx + 1].get_id() != 1 &&
		map[ty][tx + 1].get_id() != 2 && map[ty][tx + 1].get_id() != 3 &&
		_danger_map[ty][tx + 1] == 0 && (tx - floor(_x)) <= (_range - 1))
			tx = tx + 1;
		else if ((tx + 1) < SIZE_MAP_X && map[ty][tx + 1].get_id() != 1 &&
		map[ty][tx + 1].get_id() != 2 && map[ty][tx + 1].get_id() != 3 &&
		_danger_map[ty][tx + 1] == 0 && (tx - floor(_x)) > (_range - 1))
			safe = true;
		else
			return -1;
		++nbr_case;
	}
	return nbr_case;
}

int		player::check_up(std::vector<std::vector<items>> map)
{
	int		tx = floor(_x);
	int		ty = floor(_y);
	bool	safe = false;

	if ((ty - 1) > 0 &&
	(map[ty - 1][tx].get_id() != 1 &&
	map[ty - 1][tx].get_id() != 2))
		ty = ty - 1;
	else
		return -1;
	while (safe == false) {
		if ((tx - 1) >= 0 && map[ty][tx - 1].get_id() != 1 &&
		map[ty][tx - 1].get_id() != 2 && _danger_map[ty][tx - 1] == 0)
			safe = true;
		else if ((tx + 1) < SIZE_MAP_X && map[ty][tx + 1].get_id() != 1 &&
		map[ty][tx + 1].get_id() != 2 && _danger_map[ty][tx + 1] == 0)
			safe = true;
		else if ((ty - 1) >= 0 && map[ty - 1][tx].get_id() != 1 &&
		map[ty - 1][tx].get_id() != 2 && _danger_map[ty - 1][tx] == 0 &&
		(floor(_y) - ty) > (_range - 1))
			safe = true;
		else if ((ty - 1) >= 0 && map[ty - 1][tx].get_id() != 1 &&
		map[ty - 1][tx].get_id() != 2 && _danger_map[ty - 1][tx] == 0 &&
		(floor(_y) - ty) <= (_range - 1))
			ty = ty - 1;
		else
			return -1;
	}
	return 0;
}

int		player::check_down(std::vector<std::vector<items>> map)
{
	int		nbr_case = 1;
	int		tx = floor(_x);
	int		ty = floor(_y);
	bool	safe = false;

	if ((ty + 1) < SIZE_MAP_Y &&
	(map[ty + 1][tx].get_id() != 1 &&
	map[ty + 1][tx].get_id() != 2))
		ty = ty + 1;
	else
		return -1;
	while (safe == false) {
		if ((tx - 1) >= 0 && map[ty][tx - 1].get_id() != 1 &&
		map[ty][tx - 1].get_id() != 2 && map[ty][tx - 1].get_id() != 4 &&
		_danger_map[ty][tx - 1] == 0)
			safe = true;
		else if ((tx + 1) < SIZE_MAP_X && map[ty][tx + 1].get_id() != 1 &&
		map[ty][tx + 1].get_id() != 2 && map[ty][tx + 1].get_id() != 4 &&
		_danger_map[ty][tx + 1] == 0)
			safe = true;
		else if ((ty + 1) < SIZE_MAP_Y && map[ty + 1][tx].get_id() != 1 &&
		map[ty + 1][tx].get_id() != 2 && map[ty + 1][tx].get_id() != 4 &&
		_danger_map[ty + 1][tx] == 0 && (ty - floor(_y)) > (_range - 1))
			safe = true;
		else if ((ty + 1) < SIZE_MAP_Y && map[ty + 1][tx].get_id() != 1 &&
		map[ty + 1][tx].get_id() != 2 && map[ty + 1][tx].get_id() != 4
		&& _danger_map[ty + 1][tx] == 0 && (ty - floor(_y)) <= (_range - 1))
			ty = ty + 1;
		else
			return -1;
		++nbr_case;
	}
	return nbr_case;
}

bool	player::is_safe_to_bomb(std::vector<std::vector<items>> map)
{
	int		up = 0;
	int		down = 0;
	int		left = 0;
	int		right = 0;

	up = check_up(map);
	down = check_down(map);
	left = check_left(map);
	right = check_right(map);
	if (up != -1 || down != -1 || right != -1 || left != -1)
		return true;
	return false;
}

bool	player::quick_check_around(std::vector<std::vector<items>> &map)
{
	if (_danger_map[floor(_y)][floor(_x) - 1] == 0 &&
	map[floor(_y)][floor(_x) - 1].get_id() != 1 &&
	map[floor(_y)][floor(_x) - 1].get_id() != 2 &&
	map[floor(_y)][floor(_x) - 1].get_id() != 3 &&
	map[floor(_y)][floor(_x) - 1].get_id() != 4) {
		player_left(map);
		dir = LEFT;
		return true;
	}
	else if (_danger_map[floor(_y)][floor(_x) + 1] == 0 &&
	map[floor(_y)][floor(_x) + 1].get_id() != 1 &&
	map[floor(_y)][floor(_x) + 1].get_id() != 2 &&
	map[floor(_y)][floor(_x) + 1].get_id() != 3 &&
	map[floor(_y)][floor(_x) + 1].get_id() != 4) {
		player_right(map);
		dir = RIGHT;
		return true;
	}
	else if (_danger_map[floor(_y) - 1][floor(_x)] == 0 &&
	map[floor(_y) - 1][floor(_x)].get_id() != 1 &&
	map[floor(_y) - 1][floor(_x)].get_id() != 2 &&
	map[floor(_y) - 1][floor(_x)].get_id() != 3 &&
	map[floor(_y) - 1][floor(_x)].get_id() != 4) {
		player_up(map);
		dir = UP;
		return true;
	}
	else if (_danger_map[floor(_y) + 1][floor(_x)] == 0 &&
	map[floor(_y) + 1][floor(_x)].get_id() != 1 &&
	map[floor(_y) + 1][floor(_x)].get_id() != 2 &&
	map[floor(_y) + 1][floor(_x)].get_id() != 3 &&
	map[floor(_y) + 1][floor(_x)].get_id() != 4) {
		player_down(map);
		dir = DOWN;
		return true;
	}
	return false;
}

void	player::bot_movement(std::vector<std::vector<items>> map)
{
	int	mov = 0;

	if (dir != 0) {
		if (_danger_map[floor(_y) - 1][floor(_x)] == 0 &&
			map[floor(_y) - 1][floor(_x)].get_id() != 1 &&
			map[floor(_y) - 1][floor(_x)].get_id() != 2 && dir == UP) {
				player_up(map);
				return;
			}
		else if (_danger_map[floor(_y) + 1][floor(_x)] == 0 &&
			map[floor(_y) + 1][floor(_x)].get_id() != 1 &&
			map[floor(_y) + 1][floor(_x)].get_id() != 2 && dir == DOWN) {
				player_down(map);
				return;
			}
		else if (_danger_map[floor(_y)][floor(_x) - 1] == 0 &&
		map[floor(_y)][floor(_x) - 1].get_id() != 1 && dir == LEFT) {
			player_left(map);
			return;
		}
		else if (_danger_map[floor(_y)][floor(_x) + 1] == 0 &&
		map[floor(_y)][floor(_x) - 1].get_id() != 1 && dir == RIGHT) {
			player_right(map);
			return;
		}
	}
	srand(time(NULL));
	mov = rand() % 4 + 1;
	if (mov == LEFT && _danger_map[floor(_y)][floor(_x) - 1] == 0 &&
	map[floor(_y)][floor(_x) - 1].get_id() != 1 &&
	map[floor(_y)][floor(_x) - 1].get_id() != 2 &&
	map[floor(_y)][floor(_x) - 1].get_id() != 3 &&
	map[floor(_y)][floor(_x) - 1].get_id() != 4) {
		player_left(map);
		dir = mov;
	}
	else if (mov == RIGHT && _danger_map[floor(_y)][floor(_x) + 1] == 0 &&
	map[floor(_y)][floor(_x) + 1].get_id() != 1 &&
	map[floor(_y)][floor(_x) + 1].get_id() != 2 &&
	map[floor(_y)][floor(_x) + 1].get_id() != 3 &&
	map[floor(_y)][floor(_x) + 1].get_id() != 4) {
		player_right(map);
		dir = mov;
	}
	else if (mov == UP && _danger_map[floor(_y) - 1][floor(_x)] == 0 &&
	map[floor(_y) - 1][floor(_x)].get_id() != 1 &&
	map[floor(_y) - 1][floor(_x)].get_id() != 2 &&
	map[floor(_y) - 1][floor(_x)].get_id() != 3 &&
	map[floor(_y) - 1][floor(_x)].get_id() != 4) {
		player_up(map);
		dir = mov;
	}
	else if (mov == DOWN && _danger_map[floor(_y) + 1][floor(_x) + 1] == 0 &&
	map[floor(_y) + 1][floor(_x)].get_id() != 1 &&
	map[floor(_y) + 1][floor(_x)].get_id() != 2 &&
	map[floor(_y) + 1][floor(_x)].get_id() != 3 &&
	map[floor(_y) + 1][floor(_x)].get_id() != 4) {
		player_down(map);
		dir = mov;
	}
}
