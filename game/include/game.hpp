//
// EPITECH PROJECT, 2018
// game
// File description:
// game
//

#ifndef GAME_HPP_
# define GAME_HPP_

#include <irr/irrlicht.h>
#include <vector>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
#include <list>
#include <iterator>
#include "items_bonus.hpp"
#include "items.hpp"
#include "player.hpp"

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
	void	show_pos();
	void	add_indestructible();
	void	add_rock();
	void	add_ground(int x, int y);
	void	add_players();
	void	clean_angle();
	int	get_nb_players();
	player	add(bool ia, float x, float y, int num);
	std::vector<std::vector <items>>	get_map();
	std::vector<player>		get_players();
	bool	play(int action);
	void	players_turn(int action);
	void	bombs_turn();
	void	flames_turn();
	void	add_bomb(player player);
	void	add_bomb_map();
	void	add_flame(int x, int y, int range);
	void	find_bomb(int x, int y);
	void	suppr_bombs();
	void	suppr_flames();
	void	release_items(int x, int y, bool items);
	void	drawed();
	int	suppr_players();
	int	won();
private:
	std::vector<std::vector <items>>	_map;
	int					_nb_players;
	int					_nb_bots;
	int					_nb_all;
	std::vector<player>			_players;
	std::list<bomb>      			_bombs;
	int					_nb_bombs;
	std::list<flame>			_flames;
	int					_winer;
};

//15 + 2 * 11 + 2

# endif
