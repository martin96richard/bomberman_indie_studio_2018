//
// EPITECH PROJECT, 2018
// game
// File description:
// game
//

#ifndef GAME_HPP_
# define GAME_HPP_

#include <time.h>
#include <vector>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <string.h>

#define SIZE_MAP 221
#define SIZE_MAP_Y 13
#define SIZE_MAP_X 17
#define X_VALUE 0
#define Y_VALUE 1
#define O_VALUE 2

class	game
{
public:
		game();
		~game();
	void	add_wall();
	void	create_map();
	void	show_map();
	void	add_indestructible();
	void	add_rock();
	void	clean_angle();
private:
	std::vector<std::vector <int>>	_map;
	int				_nb_players;
};

//15 + 2 * 11 + 2

# endif
