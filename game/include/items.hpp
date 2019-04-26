//
// EPITECH PROJECT, 2018
// items
// File description:
// items
//

#ifndef ITEMS_HPP_
# define ITEMS_HPP_

typedef enum		e_TileType
{
	EMPTY		= 0,
	BLOCK		= 1,
	BREAKABLE	= 2,
	FLAME		= 3,
	BOMB		= 4,
	POWERUP_SPEED	= 5,
	POWERUP_RANGE	= 6,
	POWERUP_BOMB	= 7
}			tiletype;

class	items
{
public:
		items();
		~items();
	void	set_x(float x);
	void	set_y(float y);
	void	set_x_y(float x, float y);
	float	get_x();
	float	get_y();
	int	get_id();
	bool	is_new();
	void	set_new();
protected:
	float		_x;
	float		_y;
	tiletype	_id;
	bool		_new;
};

class	wall : public items
{
public:
	wall();
	~wall();
private:
	
};

class	ground : public items
{
public:
	ground();
	~ground();
private:
	
};

class	breakable : public items
{
public:
	breakable();
	~breakable();
private:
	
};

#endif
