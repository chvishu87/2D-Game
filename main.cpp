// Brian Malloy        Game Construction

//#include "manager.h"
#include "mainManager.h"
Gamedata* Gamedata::instance;

int main(int, char*[]) {
   try {
      MainManager game_manager;//Manager game_manager;
      game_manager.play();
   }
   catch (const string& msg) { std::cout << msg << std::endl; }
	 catch (const char* st)		 { std::cout << st <<std::endl; }
   catch (...) {
      std::cout << "Oops, someone threw an exception!" << std::endl;
   }
   return 0;
}
