//
// EPITECH PROJECT, 2018
// main
// File description:
// main
//

#include "DisplayGame.hpp"
#include "menu.hpp"

int main()
{
	while (1) {
		Menu menu;
		if (menu.runMenu()) {
			DisplayGame bomber(menu.getGameConfig());
			if (!bomber.handleAll()) {
				bomber.quit();
				break;
			} else
				bomber.quit();
		} else
			break;
	}
	return 0;
}
