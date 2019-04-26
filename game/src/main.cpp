//
// EPITECH PROJECT, 2018
// main
// File description:
// main
//

#include "game.hpp"
#include "sdl.hpp"

int	main()
{
	game game;
	my_lib	lib;
	bool	end = false;
	int	action = 0;

	game.create_map();
	//game.show_map();
	if (lib.init() == false)
		return 84;
	while (end != true) {
		action = lib.get_key();
		lib.get_map(game.get_map());
			lib.get_players(game.get_players(), game.get_nb_players());
		lib.delay();
		if (game.play(action) == false) {
			std::cout << "P" << game.won() << " won it !" << std::endl;
			return 0;
		}
		if (action == ESCAPE)
			end = true;
	}

//	std::cout << tata << std::endl;
//	game.show_map();
//	game.show_pos();
}
