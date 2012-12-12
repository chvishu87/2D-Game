#include <cmath>
#include "menuManager.h"

MenuManager::MenuManager() :
	CompositeManager(),
  clock( Clock::getInstance() ),
	gdata( Gamedata::getInstance() ),
  env( SDL_putenv(const_cast<char*>("SDL_VIDEO_CENTERED=center")) ),
	backSurface( IOManager::getInstance().loadAndSet(gdata->getXmlStr("back"), false) ),
	world(new Frame(backSurface,
                gdata->getXmlInt("viewWidth"), 
                gdata->getXmlInt("viewHeight"), 0, 0),2 ),
  screen( IOManager::getInstance().getScreen() ),
  gui()
  { atexit(SDL_Quit); }

void MenuManager::drawBackground() const {
	world.draw();
  //SDL_FillRect( screen, NULL, SDL_MapRGB(screen->format, 190, 190, 190) );
  //SDL_Rect dest = {0, 0, 0, 0};
  //SDL_BlitSurface( screen, NULL, screen, &dest );
}

MenuManager::MODE MenuManager::play() {
  bool keyCatch = false; // To get only 1 key per keydown
  SDL_Event event;
  bool done = false;
  bool returnKey = false;

  while ( not done ) {

    drawBackground();
    gui.draw();
    SDL_Flip(screen);

    SDL_PollEvent(&event);
    if (event.type ==  SDL_QUIT) { break; }
    if(event.type == SDL_KEYDOWN) {
      switch ( event.key.keysym.sym ) {
        case SDLK_ESCAPE : done = true; break;
        case SDLK_q      : done = true; break;
        case SDLK_RETURN : {
          if ( !keyCatch ) {
            gui.lightOn();
            returnKey = true;
          }
          break;
        }
        case SDLK_DOWN   : {
          if ( !keyCatch ) {
            gui.increment();
          }
          break;
        }
        case SDLK_UP   : {
          if ( !keyCatch ) {
            gui.decrement();
          }
          break;
        }
        default          : break;
      }
      keyCatch = true;
    }
    if(event.type == SDL_KEYUP) { 
      keyCatch = false; 
      if ( returnKey ) {
				MODE selection;
        //cout << "Chosen: " << gui.getIconClicked() << endl;
				switch(gui.getIconClicked()) {
					case "New":
						selection = START;
					case "Open":
						selection = RESUME;
					case "Save":
						selection = HELP;
					case "Help":
						selection = EXIT;
				} 
        SDL_Delay(250);
      	gui.lightOff();
				return selection;
        //done = true;
      }
    }
  }
}
