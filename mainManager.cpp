#include "mainManager.h"

MainManager::MainManager():
	CompositeManager(),
	managers()
{
	managers[0] = new Manager() ;
	managers[1] = new MenuManager();
}

MainManager::MODE MainManager::play() {
bool done = true;
MODE ret;
	while ( done ) {
		ret = managers[1]->play();
		std::cout<<ret<<std::endl;
	}
	return EXIT;
}
