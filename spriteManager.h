#ifndef SPRITEMANAGER__H
#define SPRITEMANAGER__H

#include <iostream>
#include <vector>
#include <cmath>

#include "sprite.h"
#include "multiFrameSprite.h"
#include "player.h"
#include "frameFactory.h"

class SpriteManager {
public:
	virtual ~SpriteManager() {
		std::cout<< "Reaching sprite manager destructor 1"<<std::endl;
		std::vector<Drawable*>::iterator it = spVector.begin();
		while(it != spVector.end()) {
			delete(*it);
			it++;
		}
		spVector.clear();
	std::cout<<"sprite manager destrucotr 2"<<std::endl;
	}

	SpriteManager();

	Player* getHero();
	MultiFrameSprite* getPerson();
//	Drawable* getHero();
//	MultiFrameSprite* getHero();

private:
//	std::vector<Sprite*> spVector;								// required later.
//	std::vector<MultiFrameSprite*> mspVector;
	std::vector<Drawable*> spVector;
	FrameFactory& factoryInstance;
	Gamedata* gdata;
	SpriteManager(const SpriteManager&);
	SpriteManager& operator=(SpriteManager&);
};
#endif
