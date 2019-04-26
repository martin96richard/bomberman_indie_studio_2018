//
// EPITECH PROJECT, 2018
// game
// File description:
// game
//

#ifndef GAME_HPP_
# define GAME_HPP_

#include <fstream>
#include <iostream>
#include <ios>
#include <irrlicht.h>
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
#include "SoundMgr.hpp"
#include "menu.hpp"

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
	void add_wall();
	void create_map(GameConfig data);
	void show_map();
	void show_pos();
	void add_indestructible();
	void add_rock();
	void add_ground(int x, int y);
	void add_players(Type p1, Type p2, Type p3, Type p4, int nb_p);
	void clean_angle();
	int get_nb_players();
	int get_nb_all();
	player add(bool ia, float x, float y, int num);
	std::vector<std::vector <items>> get_map();
	std::vector<player> get_players();
	bool play(std::pair<int, int> action);
	void players_turn(std::pair<int, int> action);
	void bombs_turn();
	void flames_turn();
	void add_bomb(player player);
	void add_bomb_map();
	void add_flame(int x, int y, int range);
	void find_bomb(int x, int y);
	void suppr_bombs();
	void suppr_flames();
	std::vector<int> getScores(void);
	
	void release_items(int x, int y, bool items);
	void drawed();
	int suppr_players();
	int won();
	void refresh();
	void rm_save();
	
	void save();
	void save_map();
	void save_bombs();
	void save_flames();
	void save_players();
	void save_vars();
	void load_save();
	void get_data(char *src);
	void get_save_flames();
	bomb create_bomb(int x, int y, int team, int range);
private:
	std::fstream _file;
	std::vector<std::vector <items>> _map;
	int _nb_players;
	int _nb_bots;
	int _nb_all;
	std::vector<player> _players;
	std::list<bomb>	_bombs;
	int _nb_bombs;
	std::list<flame> _flames;
	int _winer;
	bool _played;
	SoundMgr _smgr;
};

//15 + 2 * 11 + 2

# endif
