#include <cmath>
#include <sstream>
#include "menuManager.h"
#include "manager.h"

MenuManager::MenuManager() :
  env( SDL_putenv(const_cast<char*>("SDL_VIDEO_CENTERED=center")) ),
	gdata( Gamedata::getInstance() ),	
	io( IOManager::getInstance() ),
	screen(io.getScreen()),
	screenSurface(io.loadAndSet(gdata->getXmlStr("back"), false) ),//IOManager::getInstance().getScreen() ),
	world(new Frame(screenSurface,
						gdata->getXmlInt("viewWidth"),
						gdata->getXmlInt("viewHeight"), 0, 0), 2),
	clock( Clock::getInstance() ),
  //bakColor(),
  menu(),
  numberOfStars(-1)
{ 
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    throw string("Unable to initialize SDL: ");
  }
  atexit(SDL_Quit); 
}

void MenuManager::drawBackground() const {
	world.drawBG();
}

void MenuManager::getNumberOfStars() {
  IOManager& io = IOManager::getInstance().getInstance();
  SDL_Event event;
  bool done = false;
  //bool nameDone = false;
  const string msg("How many yellow stars:\\n press ESC to return to menu ");
  io.clearString();
  while ( not done ) {
    Uint8 *keystate = SDL_GetKeyState(NULL);
    if ( SDL_PollEvent(&event) )
    switch (event.type) {
      case SDL_KEYDOWN: {
        if (keystate[SDLK_ESCAPE] || keystate[SDLK_q]) {
          done = true;
        }
        /*if (keystate[SDLK_RETURN]) {
          nameDone = true;
        }*/
        io.buildString(event);
      }
    }
    drawBackground();
    io.printStringAfterMessage(msg, 20, 120);
   
    if ( !done ) {
      SDL_Flip(screen);
    }
  }
}

void MenuManager::story() {
		drawBackground();
		io.printMessageAt("Contra",350,10);
		io.printMessageAt("Before Five Years: The US Intelligenve recives information on the",10,110);
		io.printMessageAt("uprising terror groups",300,150);
		io.printMessageAt("Before Two Years: US observes invrease in terror groups activities",10,200);
		io.printMessageAt("Current: US decide to send a marine on an operation to destroy them",10,250);
		SDL_Flip(screen);
		SDL_Delay(5000);
}

void MenuManager::play() {
	story();
  bool keyCatch = false; // To get only 1 key per keydown
  SDL_Event event;
  Manager gameMan;
  bool done = false;
  while ( not done ) {

    drawBackground();
    menu.draw();
    SDL_Flip(screen);
		
    SDL_PollEvent(&event);
    if (event.type ==  SDL_QUIT) { break; }
    if(event.type == SDL_KEYDOWN) {
      switch ( event.key.keysym.sym ) {
        //case SDLK_ESCAPE :
        case SDLK_q : {
          done = true;
          break;
        }
        case SDLK_RETURN : {
          if ( !keyCatch ) {
            menu.lightOn();
            if ( menu.getIconClicked() == "Start Game" ) {
              gameMan.play();
            }
            if ( menu.getIconClicked() == "Exit" ) {
              drawBackground();
              menu.draw();
              SDL_Flip(screen);
              SDL_Delay(250);
              done = true;
            }
            if ( menu.getIconClicked() == "Help" ) {
              //getNumberOfStars();
              //gameMan.setNumberOfStars( numberOfStars );
            }
          }
          break;
        }
        case SDLK_DOWN   : {
          if ( !keyCatch ) {
            menu.increment();
          }
          break;
        }
        case SDLK_UP   : {
          if ( !keyCatch ) {
            menu.decrement();
          }
          break;
        }
        default          : break;
      }
      keyCatch = true;
    }
    if(event.type == SDL_KEYUP) { 
      keyCatch = false; 
      menu.lightOff();
    }
  }
}
