//
// EPITECH PROJECT, 2018
// game
// File description:
// game
//

#include "game.hpp"

bool	game::play(int action)
{
	drawed();
	bombs_turn();
	flames_turn();
	players_turn(action);
	add_bomb_map();
//	if (suppr_players() > -1)
//		return false;
	return true;
}

int		game::won()
{
	return _winer;
}

void		game::drawed()
{
	for (auto &map : _map)
		for(auto &_case : map)
			if (_case.is_new() == true)
				_case.set_new();
}

void		game::add_ground(int x, int y)
{
	ground	ground;

	ground.set_x_y(x, y);
	_map[y][x] = ground;
}

void		game::add_bomb_map()
{
	int	i = 0;
	int	x = 0;
	int	y = 0;

	for (auto &bomb :_bombs) {
		x = bomb.get_x();
		y = bomb.get_y();
		if (_map[y][x].get_id() == BREAKABLE)
			bomb.wall_crush();
		_map[y][x] = bomb;
		++i;
	}
}

void		game::add_bomb(player player)
{
	_bombs.push_back(player.get_bomb()[0]);
}

int		game::suppr_players()
{
	auto	it = _players.begin();
	int	win = 0;

	while (it != _players.end()) {
		if (it->is_alive() == false) {
			win = it->get_num();
			_players.erase(it);
			it = _players.begin();
		}
		else
			++it;
	}
	if (_players.size() < 1) {
		_winer = win;
		return win;
	}
	else if (_players.size() == 1) {
		_winer = _players[0].get_num();
		return _winer;
	}
	return -1;
}
	       

void		game::players_turn(int action)
{
	int	i = 0;
	bool	bomb = false;

	while (i < _nb_all) {
		if (_players[i].is_bot() == false &&
		    _players[i].is_alive() == true) {
			if (_players[i].check_bonus() == true)
				add_ground(_players[i].get_x(),
					   _players[i].get_y());
			bomb = _players[i].player_turn(_map, action);
			if (bomb == true) {
				add_bomb(_players[i]);
				bomb = false;
				++_nb_bombs;
			}
		}
		else if (_players[i].is_bot() == true &&
			 _players[i].is_alive() == true)
			_players[i].bot_turn(_map);
		++i;
	}
}

//std::cout << x << " " << y << " | " << it->get_x() << " " <<
//			it->get_y() << " is dead ->" << it->is_dead() << true << std::endl;

void		game::find_bomb(int x, int y)
{
	auto	it = _bombs.begin();

	while (it != _bombs.end()) {
		if (it->get_x() == x &&
		    it->get_y() == y &&
		    it->is_dead() == false) {
			it->set_life();
		}
		++it;
	}
}

void		game::add_flame(int x, int y, int range)
{
	int	i = 0;
	flame	flame;
	bool	left = true;
	bool	right = true;
	bool	up = true;
	bool	down = true;
	int	tpm = 0;
	int	id = 0;

	flame.set_x_y(x, y);
	_map[y][x] = flame;
	_flames.push_back(flame);
	while (++i < range) {
		if (right == true) {
			tpm = x + i;
			id = _map[y][tpm].get_id();
			if (id != BLOCK) {
				flame.set_x_y(tpm, y);
				if (id == BREAKABLE) {
					flame.set_items(true);
					right = false;
				}
				else if (id == BOMB) {
					find_bomb(tpm, y);
				}
				_map[y][tpm] = flame;
				_flames.push_back(flame);
				flame.set_items(false);
			}
			else
				right = false;
		}
		if (left == true) {
			tpm = x - i;
			id = _map[y][tpm].get_id();
			if (id != BLOCK) {
				flame.set_x_y(tpm, y);
				if (id == BREAKABLE) {
					flame.set_items(true);
					left = false;
				}
				else if (id == BOMB) {
					find_bomb(tpm, y);
				}
				_map[y][tpm] = flame;
				_flames.push_back(flame);
				flame.set_items(false);
			}
			else
				left = false;
		}
		if (up == true) {
			tpm = y - i;
			id = _map[tpm][x].get_id();
			if (id != BLOCK) {
				flame.set_x_y(x, tpm);
				if (id == BREAKABLE) {
					flame.set_items(true);
					up = false;
				}
				else if (id == BOMB) {
					find_bomb(x, tpm);
				}
				_map[tpm][x] = flame;
				_flames.push_back(flame);
				flame.set_items(false);
			}
			else
				up = false;
		}
		if (down == true) {
			tpm = y + i;
			id = _map[tpm][x].get_id();
			if (id != BLOCK) {
				flame.set_x_y(x, tpm);
				if (id == BREAKABLE) {
					flame.set_items(true);
					down = false;
				}
				else if (id == BOMB) {
					find_bomb(y, tpm);
				}
				_map[tpm][x] = flame;
				_flames.push_back(flame);
				flame.set_items(false);
			}
			else
				down = false;
		}
	}
}

void		game::bombs_turn()
{
	bool	explose = false;
	auto	it = _bombs.begin();
	
	while (it != _bombs.end() && _bombs.size() > 0) {
		explose = it->cycle();
		if (explose == true && it->is_dead() == false) {
			it->set_dead();
			add_flame(it->get_x(),
				  it->get_y(),
				  it->get_range());
		}
		if (_bombs.size() > 0)
			++it;
	}
	suppr_bombs();
}

void		game::suppr_bombs()
{
	auto	it = _bombs.begin();

	while (it != _bombs.end()) {
		if (it->is_dead() == true) {
			_bombs.erase(it);
			it = _bombs.begin();
		}
		else
			++it;
	}
}

void		game::release_items(int x, int y, bool items)
{
	ground	ground;
	bonus	loot;

	if (items == true) {
		loot.set_x_y(x, y);
		_map[y][x] = loot;
	}
	else {
		ground.set_x_y(x, y);
		_map[y][x] = ground;
	}
}

void		game::flames_turn()
{
	auto	it = _flames.begin();
	auto	end = _flames.end();
	bool	tpm = false;

	while (it != end) {
		tpm = it->cycle();
		if (tpm == true)
			release_items(it->get_x(),
				      it->get_y(),
				      it->get_items());
		++it;
	}
	suppr_flames();
}

void		game::suppr_flames()
{
	auto	it = _flames.begin();
	auto	end = _flames.end();

	while (it != end) {
		if (it->is_dead() == true) {
			_flames.erase(it);
			it = _flames.begin();
		}
		else
			++it;
	}
}
