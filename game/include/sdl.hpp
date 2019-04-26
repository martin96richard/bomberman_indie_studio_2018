//
// EPITECH PROJECT, 2018
// sdl
// File description:
// sdl
//

#ifndef SDL_HPP_
# define SDL_HPP_

#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <stdbool.h>
#include <vector>
#include "game.hpp"



# define SIZE 64
# define SNAKE 1
# define PACMAN 2

class		my_lib
{
public:
		my_lib();
		~my_lib();
	bool	create_window();
	bool	destroy_window();
	bool	load_texture();
	void	get_map(std::vector<std::vector<items>> map);
	void	get_players(std::vector<player>, int nb_players);
	int	get_key();
	void	delay();
	bool	init();
private:
	SDL_Window	*_window;
	SDL_Renderer	*_renderer;
	SDL_Texture	*_texture_ground;
	SDL_Texture	*_texture_head;
	SDL_Texture	*_texture_body;
	SDL_Texture	*_texture_food;
	SDL_Texture	*_texture_bomb;
	SDL_Texture	*_texture_flame;
	SDL_Texture	*_texture_bonus_range;
	SDL_Texture	*_texture_bonus_speed;
	SDL_Texture	*_texture_bonus_bomb;
	SDL_Event	_event;
};

#endif
