#ifndef SURFACEFACTORY__H
#define SURFACEFACTORY__H

#include <SDL.h>
#include <map>

#include "ioManager.h"
#include "gamedata.h"

class SurfaceFactory {
public:
	virtual ~SurfaceFactory();

	static SurfaceFactory& getInstance();

	SDL_Surface* getSurface (int name);

private:
	std::map<int,SDL_Surface*> surfaceContainer;
	const IOManager& io;
	const Gamedata* gdata;
	SurfaceFactory(const SurfaceFactory&);
	SurfaceFactory& operator=(const SurfaceFactory&);
	SurfaceFactory();
};
#endif
