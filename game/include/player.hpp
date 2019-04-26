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
#include <iostream>
#include <math.h>
#include "items.hpp"
#include "boom.hpp"

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
		~player();
	float	get_x();
	float	get_y();
	void	speed_up();
	void	speed_down();
	void	range_up();
	void	range_down();
	void	boom_up();
	void	boom_down();
	bool	is_bot();
	bool	player_turn(std::vector<std::vector<items>> map, int action);
	bool	bot_turn(std::vector<std::vector<items>> map);
	void	player_up(std::vector<std::vector<items>> map);
	void	player_down(std::vector<std::vector<items>> map);
	void	player_left(std::vector<std::vector<items>> map);
	void	player_right(std::vector<std::vector<items>> map);
	bool	put_bomb(std::vector<std::vector<items>> map);
	void	add_bonus(std::vector<std::vector<items>> map);
	bool	check_bonus();
	int	get_num();
	bool	is_alive();
	std::vector<bomb>	get_bomb();
private:
	unsigned int			_nb_bomb;
	unsigned int			_range;
	float				_x;
	float				_y;
	bool				_alive;
	bool				_bot;
	float				_speed;
	int				_bonus_speed;
	std::string			_name;
	int				_num;
	int				dir;
	std::vector<bomb>		_new_bomb;
	bool				_bonus;
};

#endif
