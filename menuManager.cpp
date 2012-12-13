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
	//clock( Clock::getInstance() ),
  //bakColor(),
  menu(),
  numberOfStars(-1)
{ 
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    throw string("Unable to initialize SDL: ");
  }
  //bakColor.r = Gamedata::getInstance()->getXmlInt("backgroundRed");
  //bakColor.g = Gamedata::getInstance()->getXmlInt("backgroundGreen");
  //bakColor.b = Gamedata::getInstance()->getXmlInt("backgroundBlue");
  atexit(SDL_Quit); 
}

void MenuManager::drawBackground() const {
	world.draw();
	//SDL_FillRect( screen, NULL, SDL_MapRGB(screen->format, 255,255,255) );
	//std::cout<<"drawing"<<std::endl;
  //SDL_Rect dest = {0, 0, 0, 0};
  //SDL_BlitSurface( screen, NULL, screen, &dest );
}

void MenuManager::getNumberOfStars() {
  IOManager& io = IOManager::getInstance().getInstance();
  SDL_Event event;
  bool done = false;
  bool nameDone = false;
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
    /*if ( nameDone ) {
      std::string number = io.getString();
      std::stringstream strm;
      strm << number;
      strm >> numberOfStars;
      strm.clear(); // clear error flags
      strm.str(std::string()); // clear contents
      strm << "Okay -- you'll see " << numberOfStars << " stars";
      cout << strm.str() << endl;
      io.printMessageAt(strm.str(), 20, 160);
      SDL_Flip(screen);
      SDL_Delay(400);
      done = true;
    }*/
    if ( !done ) {
      SDL_Flip(screen);
    }
  }
}

void MenuManager::play() {
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
            if ( menu.getIconClicked() == "Parameters" ) {
              getNumberOfStars();
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
