#include <SDL.h>
#include <iostream>
#include <string>
using std::cout; using std::endl; 
using std::string;

#include "ioManager.h"
#include "menu.h"
#include "clock.h"

class MenuManager {
public:
  MenuManager ();
  void play();
  int getStars() const { return numberOfStars; }

private:
  bool env;
  SDL_Surface *screen;
  const Clock& clock;

  SDL_Color bakColor;
  Menu menu;
  int numberOfStars;

  void drawBackground() const;
  MenuManager(const MenuManager&);
  MenuManager& operator=(const MenuManager&);
  void getNumberOfStars();
};
