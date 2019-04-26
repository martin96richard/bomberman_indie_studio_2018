//
// EPITECH PROJECT, 2018
// sdl
// File description:
// sdl
//

#include "sdl.hpp"

my_lib::my_lib()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
}

my_lib::~my_lib()
{
	SDL_DestroyWindow(_window);
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyTexture(_texture_ground);
	SDL_DestroyTexture(_texture_body);
	SDL_DestroyTexture(_texture_food);
	SDL_DestroyTexture(_texture_head);
	SDL_Quit();
}

bool	my_lib::	create_window()
{
	SDL_Window	*window = NULL;
	SDL_Renderer	*renderer = NULL;

	window = SDL_CreateWindow("Bomberman", 1020, 1100, 1088, 832, 0);
	if (window == NULL) {
		std::cout << "pb fonction create_window" << std::endl;
		_window = NULL;
		return false;
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	_window = window;
	_renderer = renderer;
	return true;
}

bool	my_lib::	destroy_window()
{
	SDL_DestroyWindow(_window);
	return true;
}

bool			my_lib::load_texture()
{
	_texture_ground = IMG_LoadTexture(_renderer, "texture/sand.png");
	_texture_head = IMG_LoadTexture(_renderer, "texture/fire.png");
	_texture_body = IMG_LoadTexture(_renderer, "texture/poison.png");
	_texture_food = IMG_LoadTexture(_renderer, "texture/pizza.png");
	_texture_bomb = IMG_LoadTexture(_renderer, "texture/necromancy.png");
	_texture_flame = IMG_LoadTexture(_renderer, "texture/cloud_fire2.png");
	_texture_bonus_range = IMG_LoadTexture(_renderer, "texture/bow1.png");
	_texture_bonus_speed = IMG_LoadTexture(_renderer, "texture/haste.png");
	_texture_bonus_bomb = IMG_LoadTexture(_renderer, "texture/corona.png");
	return true;
}

void				my_lib::get_map(std::vector<std::vector<items>> map)
{
	int			x = 0;
	int			y = 0;
	int			o = 0;
	SDL_Rect		SrcR;
	SDL_Rect		DestR;

	while (y < SIZE_MAP_Y) {
		while (x < SIZE_MAP_X) {
			o = map[y][x].get_id();
			SrcR.x = 0;
			SrcR.y = 0;
			SrcR.w = SIZE;
			SrcR.h = SIZE;
			DestR.x = x * SIZE;
			DestR.y = y * SIZE;
			DestR.w = SIZE;
			DestR.h = SIZE;
//			if (map[y][x].is_new() == true)
				switch (o) {
				case EMPTY:
					SDL_RenderCopy(_renderer,
						       _texture_ground,
						       &SrcR, &DestR);
					break;
				case BLOCK:
					SDL_RenderCopy(_renderer,
						       _texture_body,
						       &SrcR, &DestR);
					break;
				case BREAKABLE:
					SDL_RenderCopy(_renderer,
						       _texture_head,
						       &SrcR, &DestR);
					break;
				case BOMB:
					SDL_RenderCopy(_renderer,
						       _texture_bomb,
						       &SrcR, &DestR);
					break;
				case FLAME:
					SDL_RenderCopy(_renderer,
						       _texture_ground,
						       &SrcR, &DestR);
					SDL_RenderCopy(_renderer,
						       _texture_flame,
						       &SrcR, &DestR);
					break;
				case POWERUP_RANGE:
					SDL_RenderCopy(_renderer,
						       _texture_ground,
						       &SrcR, &DestR);
					SDL_RenderCopy(_renderer,
						       _texture_bonus_range,
						       &SrcR, &DestR);
					break;
				case POWERUP_SPEED:
					SDL_RenderCopy(_renderer,
						       _texture_ground,
						       &SrcR, &DestR);
					SDL_RenderCopy(_renderer,
						       _texture_bonus_speed,
						       &SrcR, &DestR);
					break;
				case POWERUP_BOMB:
					SDL_RenderCopy(_renderer,
						       _texture_ground,
						       &SrcR, &DestR);
					SDL_RenderCopy(_renderer,
						       _texture_bonus_bomb,
						       &SrcR, &DestR);
					break;
				}
			++x;
		}
		x = 0;
		++y;
	}
}

void   			my_lib::get_players(std::vector<player> player,
					    int nb_players)
{
	int    		i = 0;
	SDL_Rect	SrcR;
	SDL_Rect       	DestR;

	while (i < nb_players) {
		SrcR.x = 0;
		SrcR.y = 0;
		SrcR.w = SIZE;
		SrcR.h = SIZE;
		DestR.x = (player[i].get_x() - 0.5) * SIZE;
		DestR.y = (player[i].get_y() - 0.5) * SIZE;
		DestR.w = SIZE;
		DestR.h = SIZE;
		SDL_RenderCopy(_renderer,
			       _texture_food, &SrcR, &DestR);
		++i;
	}
	SDL_RenderPresent(_renderer);
}

int			my_lib::get_key()
{
	while (SDL_PollEvent(&_event) == 1) {
		if (_event.type == SDL_KEYDOWN)
			switch (_event.key.keysym.sym) {
			case SDLK_LEFT:
				return LEFT;
			case SDLK_RIGHT:
				return RIGHT;
			case SDLK_UP:
				return UP;
			case SDLK_DOWN:
				return DOWN;
			case SDLK_ESCAPE:
				return ESCAPE;
			case SDLK_SPACE:
				return PUT_BOMB;

			}
		if (_event.window.event == SDL_WINDOWEVENT_CLOSE)
			return 5;
	}
	return 0;
}

void	my_lib::delay()
{
	SDL_Delay(75);
}

bool		my_lib::init()
{
	if (create_window() == false ||
	    load_texture() == false)
		return false;
	return true;
}

extern "C"
{
	__attribute__((__constructor__))my_lib	*createlib()
	{
		return new my_lib;
	}

	__attribute__((__destructor__))void	destroylib()
	{
		return;
	}
}
