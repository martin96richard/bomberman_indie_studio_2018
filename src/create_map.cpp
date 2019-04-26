//
// EPITECH PROJECT, 2018
// game
// File description:
// game
//

#include "game.hpp"

game::game()
{
	_nb_players = 0;
	_nb_bots = 0;
	_nb_all = 0;
	_nb_bombs = 0;
	_played = false;
	_smgr.playMusic();
}

game::~game()
{
}

void game::create_map(GameConfig data)
{
	ground	ground;
	int x = 0;
	int y = 0;
	std::vector<items> tpm;

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
	add_players(data.players->P1, data.players->P2,
		    data.players->P3, data.players->P4, data.players->nb_P);
}

player game::add(bool ia, float x, float y, int num)
{
	player dest(ia, x, y, num);

	return dest;
}

void game::add_players(Type p1, Type p2, Type p3, Type p4, int nb_p)
{
	int i = 0;
	float x = 1;
	float y = 1;
	int num = 1;

	_nb_all = nb_p;
	if (p1 == HUMAN) {
		_players.push_back(add(false, x, y, num));
		++_nb_players;
	}
	else if (p1 == IA) {
		_players.push_back(add(true, x, y, num));
		++_nb_bots;
	}
	x = 14.5;
	num = 2;
	if (p2 == HUMAN) {
		_players.push_back(add(false, x, y, num));
		++_nb_players;
	}
	else if (p2 == IA) {
		_players.push_back(add(true, x, y, num));
		++_nb_bots;
	}
	x = 1.5;
	y = 11.5;
	num = 3;
	if (p3 == HUMAN) {
		_players.push_back(add(false, x, y, num));
		++_nb_players;
	}
	else if (p3 == IA) {
		_players.push_back(add(true, x, y, num));
		++_nb_bots;
	}
	x = 14.5;
	num = 4;
	if (p4 == HUMAN) {
		_players.push_back(add(false, x, y, num));
		++_nb_players;
	}
	else if (p4 == IA) {
		_players.push_back(add(true, x, y, num));
		++_nb_bots;
	}
}

void game::add_wall()
{
	int y = 0;
	int x = 0;
	wall wall;

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

void game::add_indestructible()
{
	int x = 0;
	int y = 0;
	wall wall;

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

void game::add_rock()
{
	int tpm = 0;
	int x = 0;
	int y = 0;
	breakable breakable;

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

void game::clean_angle()
{
	int x = 0;
	int y = 0;
	ground ground;

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

void game::show_map()
{
	int y = -1;
	int x = -1;

	while (++y < SIZE_MAP_Y) {
		while (++x < SIZE_MAP_X)
			if (_map[y][x].is_new() == true)
				std::cout << _map[y][x].get_id() << " ";
		std::cout << std::endl;
		x = -1;
	}
}

std::vector<std::vector<items>>	game::get_map()
{
	return _map;
}

int game::get_nb_players()
{
	return _nb_players;
}

std::vector<player> game::get_players()
{
	return _players;
}

void game::save_players()
{
	auto it = _players.begin();

	_file << "\nPLAYERS\n";
	while (it != _players.end()) {
		it->save(_file);
		++it;
	}
}

void game::save_bombs()
{
	auto it = _bombs.begin();

	_file << "\nBOMBS\n";
	while (it != _bombs.end()) {
		it->save(_file);
		++it;
	}
}

void game::save_flames()
{
	auto it = _flames.begin();

	_file << "\nFLAMES\n";
	while (it != _flames.end()) {
		it->save(_file);
		++it;
	}
}

void game::save_map()
{
	_file << "\nMAP" << std::endl;
	for (auto &map : _map)
		for(auto &_case : map)
			_file << _case.get_id() << " ";
}

void game::save_vars()
{
	_file << "GAME" << std::endl;
	_file << _nb_players << " " << _nb_bots << " "
	      << _nb_all << " " << _nb_bombs << ";";
}

void game::save()
{
	_file.open("save", std::ios::out | std::ios::trunc);
	save_vars();
	save_map();
	save_players();
	save_bombs();
	save_flames();
	_file.close();
}

void game::rm_save()
{
	std::fstream file;

	_file.open("save", std::ios::out | std::ios::trunc);
	_file << "";
}

bomb game::create_bomb(int x, int y, int team, int range)
{
	bomb bomb(x, y, team, range);

	return (bomb);
}

void game::get_save_flames()
{
	int x = 0;
	int y = 0;
	flame flame;

	_flames.clear();
	while (y < SIZE_MAP_Y) {
		while (x < SIZE_MAP_X) {
			if (_map[y][x].get_id() == FLAME) {
				flame.set_x_y(x, y);
				_flames.push_back(flame);
			}
			++x;
		}
		x = 0;
		++y;
	}
}

void game::get_data(char *src)
{
	items ground;
	int x = 0;
	int y = 0;
	int i = 0;
	std::vector<items> tpm;
	player player;

	strtok(src, "\n ;");
	_nb_players = atoi(strtok(NULL, "\n ;"));
	_nb_bots = atoi(strtok(NULL, "\n ;"));
	_nb_all = atoi(strtok(NULL, "\n ;"));
	_nb_bombs = atoi(strtok(NULL, "\n ;"));
	strtok(NULL, "\n ;");
	_map.clear();
	while (y < SIZE_MAP_Y) {
		while (x < SIZE_MAP_X) {
			ground.set_x_y(x, y);
			ground.set_id((tiletype) atof(strtok(NULL, "\n ;")));
			tpm.push_back(ground);
			++x;
		}
		_map.push_back(tpm);
		tpm.clear();
		x = 0;
		++y;
	}
	strtok(NULL, "\n ;");
	_players.clear();
	float	x_;
	float	y_;
	bool	ia;
	int	team;
	while (i < _nb_all) {
		ia = (bool) atof(strtok(NULL, "\n ;"));
		x_ = atof(strtok(NULL, "\n ;"));
		y_ = atof(strtok(NULL, "\n ;"));
		team = atoi(strtok(NULL, "\n ;"));
		player = add(ia, x_, y_, team);
		player.get_save();
		_players.push_back(player);
		++i;
	}
	strtok(NULL, "\n ;");
	i = 0;
	_bombs.clear();
	while (i < _nb_bombs) {
		std::cout << "cccc" << std::endl;
		_bombs.push_back(create_bomb(atof(strtok(NULL, "\n ;")),
					     atof(strtok(NULL, "\n ;")),
					     atof(strtok(NULL, "\n ;")),
					     atof(strtok(NULL, "\n ;"))));
		++i;
	}
	get_save_flames();
	strtok(NULL, "\n ;");
}

void game::load_save()
{
	std::ifstream fs("save");
	char c;
	std::string dest;
	const char *real;

	if (fs.good() == true)
		while (fs.get(c))
			dest += c;
	real = dest.c_str();
	get_data(strdup(real));
	fs.close();
}
