#ifndef MANAGER__H
#define MANAGER__H

#include <SDL.h>
#include <iostream>
#include <string>
#include <vector>

#include "ioManager.h"
#include "clock.h"
#include "gamedata.h"
#include "sprite.h"
#include "multiFrameSprite.h"
#include "world.h"
#include "viewport.h"
#include "spriteManager.h"
#include "bulletFactory.h"
#include "collisionStrategy.h"
#include "explodingSprite.h"
#include "sound.h"

class Manager {
public:
  Manager ();
  ~Manager ();
  void play();

private:
  const bool env;
	int bitset;
	bool helpFlag;
  const Gamedata* gdata;
  const IOManager& io;
  Clock& clock;
	BulletFactory& bullets;

  SDL_Surface *screen;
  SDL_Surface * const backSurface;
  World world;
	SDL_Surface * const bgSurface;
	World bgworld;
  Viewport& viewport;
	SpriteManager *sp;
	Player* hero;

	std::vector<CollisionStrategy*> strategies;
	CollisionStrategy * collisionStrategy;

	std::vector<Drawable*> redorb;
	std::list<ExplodingSprite*> redorbEx;
  //std::vector<MultiFrameSprite *> redorb;
	unsigned currentObject;

	SDLSound sound;
	bool del;
	void checkForCollision();
	void setRedOrb();
  void draw() const;
  void update(Uint32);
  Manager(const Manager&);
  Manager& operator=(const Manager&);
};

#endif
