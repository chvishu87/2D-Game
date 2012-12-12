#include <SDL.h>
#include <iostream>
#include <string>
using std::cout; using std::endl; 
using std::string;

#include "ioManager.h"
#include "gui.h"
#include "clock.h"
#include "world.h"
#include "gamedata.h"
#include "compositeManager.h"

class MenuManager : public CompositeManager {
public:
  MenuManager ();
  virtual MODE play();

private:
  const Clock& clock;
	const Gamedata* gdata;
  bool env;

	SDL_Surface * const backSurface;
	World world;
  SDL_Surface *screen;
  Gui gui;

  void drawBackground() const;

  MenuManager(const MenuManager&);
  MenuManager& operator=(const MenuManager&);
};
