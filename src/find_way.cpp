/*
** EPITECH PROJECT, 2018
** find_way
** File description:
** find_way
*/

#include "game.hpp"

void	       	show_map(std::vector<std::vector<int>> move_map)
{
	int	y = -1;
	int	x = -1;

	while (++y < SIZE_MAP_Y) {
		while (++x < SIZE_MAP_X)
			std::cout << move_map[y][x] << " ";
		std::cout << std::endl;
                x = -1;
	}
}

static void	init_map(int px, int py,
			std::vector<std::vector<items>> map,
			std::vector<std::vector<int>> &move_map)
{
	std::vector<int>				tmp;
	int							x = 0;
	int							y = 0;

	while (y < SIZE_MAP_Y) {
		while (x < SIZE_MAP_X) {
			if (map[y][x].get_id() == 1 || map[y][x].get_id() == 2)
				tmp.push_back(-1);
			else
				tmp.push_back(0);
			++x;
		}
		move_map.push_back(tmp);
		tmp.clear();
		x = 0;
		++y;
	}
	move_map[py][px] = -2;
	if (map[py][px + 1].get_id() != 1 && map[py][px + 1].get_id() != 2 &&
		map[py][px + 1].get_id() != 4)
		move_map[py][px + 1] = 1;
	if (map[py][px - 1].get_id() != 1 && map[py][px - 1].get_id() != 2 &&
		map[py][px - 1].get_id() != 4)
		move_map[py][px - 1] = 1;
	if (map[py + 1][px].get_id() != 1 && map[py + 1][px].get_id() != 2 &&
		map[py + 1][px].get_id() != 4)
		move_map[py + 1][px] = 1;
	if (map[py - 1][px].get_id() != 1 && map[py - 1][px].get_id() != 2 &&
		map[py - 1][px].get_id() != 4)
		move_map[py - 1][px] = 1;
}

static void	init_dir(int px, int py, std::vector<std::vector<int>>	&dir_map)
{
	std::vector<int>				tmp;
	int							x = 0;
	int							y = 0;

	while (y < SIZE_MAP_Y) {
		while (x < SIZE_MAP_X) {
				tmp.push_back(0);
			++x;
		}
		dir_map.push_back(tmp);
		tmp.clear();
		x = 0;
		++y;
	}
	dir_map[py][px + 1] = RIGHT;
	dir_map[py][px - 1] = LEFT;
	dir_map[py + 1][px] = DOWN;
	dir_map[py - 1][px] = UP;
}

int		player::check_around(std::vector<std::vector<int>>	&move_map,
		std::vector<std::vector<int>>	&dir_map, int dist)
{
	int								x = 0;
	int								y = 0;

	while (y < SIZE_MAP_Y) {
		while (x < SIZE_MAP_X) {
			if (move_map[y][x] == dist && (x + 1) < SIZE_MAP_X &&
			move_map[y][x + 1] == 0) {
				dir_map[y][x + 1] = dir_map[y][x];
				move_map[y][x + 1] = dist + 1;
				if (_danger_map[y][x + 1] == 0) {
					return (dir_map[y][x + 1]);
				}
			}
			if (move_map[y][x] == dist && (x - 1) >= 0 &&
			move_map[y][x - 1] == 0) {
				dir_map[y][x - 1] = dir_map[y][x];
				move_map[y][x - 1] = dist + 1;
				if (_danger_map[y][x - 1] == 0) {
					return (dir_map[y][x - 1]);
				}
			}
			if (move_map[y][x] == dist && (y + 1) < SIZE_MAP_Y &&
			move_map[y + 1][x] == 0) {
				dir_map[y + 1][x] = dir_map[y][x];
				move_map[y + 1][x] = dist + 1;
				if (_danger_map[y + 1][x] == 0) {
					return (dir_map[y + 1][x]);
				}
			}
			if (move_map[y][x] == dist && (y -1) >= 0 &&
				move_map[y - 1][x] == 0) {
				dir_map[y - 1][x] = dir_map[y][x];
				move_map[y - 1][x] = dist + 1;
				if (_danger_map[y - 1][x] == 0) {
					return (dir_map[y - 1][x]);
				}
			}
			++x;
		}
		x = 0;
		++y;
	}
	return (-1);
}

void		player::escape(std::vector<std::vector<items>> map)
{
	std::vector<std::vector<int>>	move_map;
	std::vector<std::vector<int>>	dir_map;
	int								dist = 1;
	int								dir = 0;

	init_map(floor(_x), floor(_y), map, move_map);
	init_dir(floor(_x), floor(_y), dir_map);
	while (dist < 10) {
		dir = check_around(move_map, dir_map, dist);
		if (dir != -1) {
			switch (dir) {
				case 3: {
					player_left(map);
					return;
				}
				case 4: {
					player_right(map);
					return;
				}
				case 1: {
					player_up(map);
					return;
				}
				case 2: {
					player_down(map);
					return;
				}
			}
		}
		++dist;
	}
}
