#ifndef BULLETFACTORY__H
#define BULLETFACTORY__H

#include <list>

#include "sprite.h"
#include "frameFactory.h"
#include "gamedata.h"

class BulletFactory {
public:
	static BulletFactory& getInstance();
	virtual ~BulletFactory();// { std::cout<<"Bullet factory destrucotr"<<std::endl; }
	Sprite* getBullet(float, float, int);
	Sprite* getEnemyBullet(float, float, int);
	void draw();
	void update(Uint32);
	std::list<Sprite*>& getBulletList() { return activeBullets; }
	std::list<Sprite*>& getEnemyBulletList() { return inactiveBullets; }
	std::list<Sprite*>& getInactiveBulletList() { return inactiveBullets; }
private:
	std::list<Sprite*> activeBullets;
	std::list<Sprite*> activeEnemyBullets;
	std::list<Sprite*> inactiveBullets;
	FrameFactory& factoryInstance;
	const Gamedata* gdata;
	BulletFactory();
	BulletFactory(const BulletFactory&);
	BulletFactory& operator=(const BulletFactory&);
};

#endif
