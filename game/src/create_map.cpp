//
// EPITECH PROJECT, 2018
// game
// File description:
// game
//

#include "game.hpp"

game::game()
{
	_nb_players = 1;
	_nb_bots = 3;
	_nb_all = 1;
	_nb_bombs = 0;
}

game::~game()
{
}

void				game::create_map()
{
	ground			ground;
	int			x = 0;
	int			y = 0;
	std::vector<items>	tpm;

        while (y < SIZE_MAP_Y) {
                while (x < SIZE_MAP_X) {
			ground.set_x_y(x, y);
			tpm.push_back(ground);
			++x;
                }
		_map.push_back(tpm);
		tpm.clear();
                x = 0;
 	        ++y;
        }
	add_wall();
	add_indestructible();
	add_rock();
	clean_angle();
	add_players();
}

player		game::add(bool ia, float x, float y, int num)
{
	player	dest(ia, x, y, num);

	return dest;
}

void			game::add_players()
{
	int		i = 0;
	float		x = 1;
	float		y = 1;
	int		num = 1;

	while (i < _nb_players) {
		_players.push_back(add(false, x, y, num));
		++num;
		if (i == 1)
			x = 15;
		else if ( i == 2) {
			x = 1;
			y = 11;
		}
		else
			x = 15;
		++i;
	}
}

void		game::add_wall()
{
	int	y = 0;
	int	x = 0;
	wall	wall;

	while (y < SIZE_MAP_Y) {
		if (y == 0 || y == 12)
			while (x < SIZE_MAP_X) {
				_map[y][x] = wall;
				_map[y][x].set_x_y(x, y);
				++x;
			}
		_map[y][0] = wall;
		_map[y][0].set_x_y(0, y);
		_map[y][16] = wall;
		_map[y][16].set_x_y(16, y);
		x = 0;
		++y;
	}
}

void		game::add_indestructible()
{
	int	x = 0;
	int	y = 0;
	wall	wall;

	while (y < SIZE_MAP_Y) {
		while (x < SIZE_MAP_X) {
			if (y % 2 == 0 && x % 2 == 0) {
				_map[y][x] = wall;
				_map[y][x].set_x_y(x, y);
			}
			++x;
		}
		x = 0;
		++y;
	}
}

void			game::add_rock()
{
	int		tpm = 0;
	int		x = 0;
	int		y = 0;
	breakable	breakable;

	srand(time(NULL));
	while (y < SIZE_MAP_Y) {
		while (x < SIZE_MAP_X) {
			if (_map[y][x].get_id() == 0) {
				tpm = rand() % 10;
				++tpm;
				if (tpm > 4)
					_map[y][x] = breakable;
				_map[y][x].set_x_y(x, y);
			}
			++x;
		}
		x = 0;
		++y;
	}
}

void	game::clean_angle()
{
	int	x = 0;
	int	y = 0;
	ground	ground;

	while (y < SIZE_MAP_Y) {
		while (x < SIZE_MAP_X) {
			if ((x == 1 && y == 1) ||
			    (x == 2 && y == 1) ||
			    (x == 1 && y == 2) ||
			    (x == 1 && y == 11) ||
			    (x == 2 && y == 11) ||
			    (x == 1 && y == 10) ||
			    (x == 15 && y == 1) ||
			    (x == 15 && y == 2) ||
			    (x == 14 && y == 1) ||
			    (x == 15 && y == 11) ||
			    (x == 15 && y == 10) ||
			    (x == 14 && y == 11)) {
				_map[y][x] = ground;
				_map[y][x].set_x_y(x, y);
			}
			++x;
		}
		x = 0;
		++y;
	}
}

//		for (const auto &value : elem)

void	       	game::show_map()
{
	int	y = -1;
	int	x = -1;

	while (++y < SIZE_MAP_Y) {
		while (++x < SIZE_MAP_X)
			std::cout << _map[y][x].get_id() << " ";
		std::cout << std::endl;
                x = -1;
	}
}

void	       	game::show_pos()
{
	int	y = -1;
	int	x = -1;

	while (++y < SIZE_MAP_Y) {
		while (++x < SIZE_MAP_X)
			std::cout << _map[y][x].get_x() <<
				_map[y][x].get_y() << " ";
		std::cout << std::endl;
                x = -1;
	}
}

std::vector<std::vector <items>>	game::get_map()
{
	return _map;
}

int	game::get_nb_players()
{
	return _nb_players;
}

std::vector<player>	game::get_players()
{
	return _players;
}
