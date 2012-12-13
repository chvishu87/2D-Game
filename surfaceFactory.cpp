#include "surfaceFactory.h"

SurfaceFactory::~SurfaceFactory() {
	std::cout<<"surfacefacotry destructor 1"<<std::endl;
	std::map<int, SDL_Surface*>::iterator itr = surfaceContainer.begin();
	while(itr != surfaceContainer.end()) {
		SDL_FreeSurface(itr->second);
		itr++;
	}
	surfaceContainer.clear();
	std::cout<<"surfacefacotry destructor 2"<<std::endl;
}

SurfaceFactory::SurfaceFactory():
	surfaceContainer(),
	io(IOManager::getInstance()),
	gdata(Gamedata::getInstance())
	{}

SurfaceFactory& SurfaceFactory::getInstance() {
	static SurfaceFactory surface;
	return surface;
}

SDL_Surface* SurfaceFactory::getSurface (int name) {
	SDL_Surface* surface = NULL;
	if (surfaceContainer.find(name) != surfaceContainer.end()) {
		surface = surfaceContainer[name];
	} else {
		switch(name) {
			case 1:
				surface = io.loadAndSet(gdata->getXmlStr("redorbFile"), true);
				break;
			case 2:
				surface = io.loadAndSet(gdata->getXmlStr("bulletImg"), true);
				break;
			case 3:
				surface = io.loadAndSet(gdata->getXmlStr("blueorbFile"), true);
				break;
			default:
				throw("Surface is not available");
		}
		surfaceContainer[name] = surface;
	}
	return surface;
}
