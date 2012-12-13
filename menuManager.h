#include <SDL.h>
#include <iostream>
#include <string>
using std::cout; using std::endl; 
using std::string;

#include "ioManager.h"
#include "menu.h"
#include "clock.h"
#include "world.h"

class MenuManager {
public:
  MenuManager ();
  void play();
  int getStars() const { return numberOfStars; }

private:
  bool env;
	const Gamedata* gdata;
	const IOManager& io;
	
	SDL_Surface *screen;
  SDL_Surface *screenSurface;
	World world;
  Clock& clock;

  //SDL_Color bakColor;
  Menu menu;
  int numberOfStars;

  void drawBackground() const;
  MenuManager(const MenuManager&);
  MenuManager& operator=(const MenuManager&);
  void getNumberOfStars();
	void story();
};
