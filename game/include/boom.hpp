//
// EPITECH PROJECT, 2018
// boom
// File description:
// boom
//

#ifndef BOOM_HPP_
# define BOOM_HPP_

#include "items.hpp"
#include <iostream>

class bomb : public items
{
public:
		bomb(int x, int y, int team, int range);
		~bomb();
	void	wall_crush();
	bool	cycle();
	int	get_range();
	void	set_dead();
	void	set_life();
	bool	is_dead();
private:
	int	_range;
	int	_team;
	int	_life;
	int	_type;
	bool	_item;
	bool	_dead;
};

class flame : public items
{
public:
		flame();
		~flame();
	bool	get_items();
	void	set_items(bool items);
	bool	cycle();
	bool	is_dead();
private:
	bool	_items;
	int	_life;
	bool	_dead;
};

#endif
