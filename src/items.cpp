//
// EPITECH PROJECT, 2018
// items
// File description:
// items
//

#include "items.hpp"

items::items()
{
	_x = -1;
	_y = -1;
	_new = true;
}

items::~items()
{
}

void items::set_id(tiletype id)
{
	_id = id;
}

void items::set_new(bool _this)
{
	_new = _this;
}

bool items::is_new()
{
	return _new;
}

void items::set_x(float x)
{
	_x = x;
	return;
}

void items::set_y(float y)
{
	_y = y;
	return;
}

void items::set_x_y(float x, float y)
{
	_y = y;
	_x = x;
	_new = true;
	return;
}

float items::get_x()
{
	return (_x);
}

float items::get_y()
{
	return (_y);
}

int items::get_id()
{
	return (_id);
}

wall::wall()
{
	_id = BLOCK;
}

wall::~wall()
{
}

ground::ground()
{
	_id = EMPTY;
}

ground::~ground()
{
}

breakable::breakable()
{
	_id = BREAKABLE;
}

breakable::~breakable()
{
}
