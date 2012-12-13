#include "bulletFactory.h"

BulletFactory::BulletFactory() :
		activeBullets(),
		activeEnemyBullets(),
		inactiveBullets(),
		factoryInstance(FrameFactory::getInstance()),
		gdata(Gamedata::getInstance())
		{}

BulletFactory& BulletFactory::getInstance() {
	static BulletFactory instance;
	return instance;
}

BulletFactory::~BulletFactory() {
	if(activeBullets.size() > 0) {
		std::list<Sprite*>::iterator it = activeBullets.begin();
		while(it != activeBullets.end()) {
			delete (*it);
			++it;
		}
	}
	activeBullets.clear();

	if(inactiveBullets.size() > 0) {
		std::list<Sprite*>::iterator it = inactiveBullets.begin();
		while(it != inactiveBullets.end()) {
			delete (*it);
			++it;
		}
	}
	inactiveBullets.clear();
}

Sprite* BulletFactory::getBullet(float x, float y, int i) {
	std::list<Sprite*>::iterator it;
	Sprite* bullet;
	int direction;

	if(i == 1)
		direction = gdata->getXmlInt("bulletXspeed");
	else if(i == 0)
		direction = -(gdata->getXmlInt("bulletXspeed"));

	if(!inactiveBullets.empty()) {
		it = inactiveBullets.begin();
		inactiveBullets.pop_front();
		bullet = *it;
		bullet->X(x);
		bullet->Y(y);
		bullet->velocityX(direction);

		// modify the sprite object value here.
		activeBullets.push_back(*it);
	}	else {
		bullet = new Sprite(Vector2f(static_cast<int>(x),static_cast<int>(y)),				// -------get the position based on the sprite position.-------
												Vector2f(direction,gdata->getXmlInt("bulletYspeed")),	// ---set the x direction velocity based on the sprite direction.---
												"bullet",factoryInstance.getFrame(7));
		activeBullets.push_back(bullet);	// create a new bullet and insert it into the list.
	}
	return bullet;
}

Sprite* BulletFactory::getEnemyBullet(float x, float y, int i) {
	std::list<Sprite*>::iterator it;
	Sprite* bullet;
	int direction;

	if(i == 1)
		direction = gdata->getXmlInt("bulletXspeed");
	else if(i == 0)
		direction = -(gdata->getXmlInt("bulletXspeed"));

	if(!inactiveBullets.empty()) {
		it = inactiveBullets.begin();
		inactiveBullets.pop_front();
		bullet = *it;
		bullet->X(x);
		bullet->Y(y);
		bullet->velocityX(direction);

		// modify the sprite object value here.
		activeEnemyBullets.push_back(*it);
	}	else {
		bullet = new Sprite(Vector2f(static_cast<int>(x),static_cast<int>(y)),				// -------get the position based on the sprite position.-------
												Vector2f(direction,gdata->getXmlInt("bulletYspeed")),	// ---set the x direction velocity based on the sprite direction.---
												"bullet",factoryInstance.getFrame(7));
		activeEnemyBullets.push_back(bullet);	// create a new bullet and insert it into the list.
	}
	return bullet;
}

void BulletFactory::draw() {
	if(activeBullets.size() != 0) {
		std::list<Sprite*>::iterator it = activeBullets.begin();
		while (it != activeBullets.end()) {
			(*it)->draw();
			it++;
		}
	}
	if(activeEnemyBullets.size() != 0) {
		std::list<Sprite*>::iterator it = activeEnemyBullets.begin();
		while (it != activeEnemyBullets.end()) {
			(*it)->draw();
			it++;
		}
	}
	
}

void BulletFactory::update(Uint32 ticks) {
	std::cout<<activeEnemyBullets.size()<<std::endl;
	std::list<Sprite*>::iterator it = activeBullets.begin();
	while (it != activeBullets.end()) {
		(*it)->update(ticks);
		if(!((*it)->inView())) {		// need to implement inView()
			Sprite* temp = *it;
			it = activeBullets.erase(it);
			//it++;
			inactiveBullets.push_back(temp);
		}	else {
			it++;
		}
	}
	
	std::list<Sprite*>::iterator itr = activeEnemyBullets.begin();
	while ( itr != activeEnemyBullets.end() ) {
		(*itr)->update(ticks);
		if(!((*itr)->inView())) {		// need to implement inView()
			Sprite* temp = *itr;
			itr = activeEnemyBullets.erase(itr);
			//it++;
			inactiveBullets.push_back(temp);
		}	else {
			itr++;
		}
	}
}
