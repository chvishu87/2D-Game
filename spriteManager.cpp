#include "spriteManager.h"

SpriteManager::SpriteManager():
	spVector(),
//	mspVector(),
	factoryInstance(FrameFactory::getInstance()),
	gdata(Gamedata::getInstance())
	{}

//MultiFrameSprite* SpriteManager::getPerson() {
Enemy* SpriteManager::getPerson() {
	std::vector<Frame*> frameset;
	for(int i = 1; i <=6 ; i++)
		frameset.push_back(factoryInstance.getFrame(i));
	/*MultiFrameSprite**/Enemy* person = new /*MultiFrameSprite*/Enemy(Vector2f(rand()%gdata->getXmlInt("worldWidth"),120),
																	Vector2f(gdata->getXmlInt("redorbXspeed"),gdata->getXmlInt("redorbYspeed")),
																	"redorb",frameset);
	spVector.push_back(person);
	return person;
}

Player* SpriteManager::getHero() {
	std::vector<Frame*> frameset;
	
	for(int i = 1 ; i <= 6 ; i++)
		frameset.push_back(factoryInstance.getFrame(i));

	Player *hero = new Player(Vector2f(rand()%gdata->getXmlInt("worldWidth"),120),Vector2f(100,0),"redorb",frameset);
	spVector.push_back(hero);
	return hero;
}
