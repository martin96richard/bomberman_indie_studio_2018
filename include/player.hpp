//
// EPITECH PROJECT, 2018
// player
// File description:
// player
//

#ifndef PLAYER_HPP_
# define PLAYER_HPP_

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <math.h>
#include <list>
#include <string.h>
#include "items.hpp"
#include "boom.hpp"
#include "SoundMgr.hpp"

#define HIT_BOX 0.40
#define NONE 0
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#define PUT_BOMB 6
#define MOVE 0.17
#define ESCAPE 5
#define HIT 0.40

class player
{
public:
	player(bool is_bot, float x, float y, int _num);
	player();
	~player();

	float get_x();
	float get_y();
	void speed_up();
	void speed_down();
	void range_up();
	void range_down();
	void boom_up();
	void boom_down();
	bool is_bot();
	bool player_turn(std::vector<std::vector<items>> map,
					    int action, std::list<bomb> bomb);
	bool bot_turn(std::vector<std::vector<items>> map, std::list<bomb> bombs);
	void player_up(std::vector<std::vector<items>> map);
	void player_down(std::vector<std::vector<items>> map);
	void player_left(std::vector<std::vector<items>> map);
	void player_right(std::vector<std::vector<items>> map);
	bool put_bomb(std::vector<std::vector<items>> map, std::list<bomb> bomb);
	int getScore(void);
	bool getCheckDir(void);
	void setCheckDir(bool checked);
	void add_bonus(std::vector<std::vector<items>> map);
	bool check_bonus(void);
	int get_num(void);
	bool is_alive(void);
	bomb create_bomb(int x, int y, int team, int range);
	std::vector<bomb> get_bomb();
	void save(std::fstream &file);
	void get_save();
private:
	void	get_danger_map(std::list<bomb> bombs, std::vector<std::vector<items>> map);
	void	set_range_on_map(std::vector<std::vector<items>> map, int range, int x, int y);
	bool	is_safe_to_bomb(std::vector<std::vector<items>> map);
	int	check_left(std::vector<std::vector<items>> map);
	int	check_right(std::vector<std::vector<items>> map);
	int	check_up(std::vector<std::vector<items>> map);
	int	check_down(std::vector<std::vector<items>> map);
	void	bot_movement(std::vector<std::vector<items>> map);
	void	escape(std::vector<std::vector<items>> map);
	int check_around(std::vector<std::vector<int>>	&move_map,
			 std::vector<std::vector<int>>	&dir_map, int dist);
	bool	quick_check_around(std::vector<std::vector<items>> &map);
	bool _bot;
	float _x;
	float _y;
	bool _dirCheck;
	int _num;
	float _speed;
	int _bonus_speed;
	bool _bonus;
	unsigned int _nb_bomb;
	unsigned int _range;
	bool _alive;
	std::vector<bomb> _new_bomb;
	int _score;
	SoundMgr _smgr;
	std::vector<std::vector<int>>	_danger_map;
	int	dir;
};

#endif
