#include "spriteManager.h"

SpriteManager::SpriteManager():
	spVector(),
//	mspVector(),
	factoryInstance(FrameFactory::getInstance()),
	gdata(Gamedata::getInstance()),
	gap(0)
	{}

Enemy* SpriteManager::getPerson() {
	std::vector<Frame*> frameset;
	for(int i = 8 ; i <= 13 ; i++)
		frameset.push_back(factoryInstance.getFrame(i));
	/*Enemy* person = new Enemy(Vector2f(rand()%gdata->getXmlInt("worldWidth"),120),
																	Vector2f(gdata->getXmlInt("redorbXspeed"),gdata->getXmlInt("redorbYspeed")),
																	"redorb",frameset);*/
	Enemy* person = new Enemy(Vector2f(gdata->getXmlInt("worldWidth")-gap,120),
																	Vector2f(gdata->getXmlInt("redorbXspeed"),gdata->getXmlInt("redorbYspeed")),
																	"blueorb",frameset);

	spVector.push_back(person);
	gap = gap + 100;
	if((gdata->getXmlInt("worldWidth") - gap)<=0)
		gap = 0;
	return person;
}

Player* SpriteManager::getHero() {
	std::vector<Frame*> frameset;
	
	for(int i = 1 ; i <= 6 ; i++)
		frameset.push_back(factoryInstance.getFrame(i));

	Player *hero = new Player(Vector2f(10,120),Vector2f(100,0),"redorb",frameset);
	spVector.push_back(hero);
	return hero;
}
