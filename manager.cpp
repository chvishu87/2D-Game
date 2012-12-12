#include <cmath>
#include "manager.h"

Manager::~Manager() { 
  delete Gamedata::getInstance();
	SDL_FreeSurface(backSurface);
	SDL_FreeSurface(screen);
	delete sp;

	std::vector<CollisionStrategy*>::iterator itr = strategies.begin();
	while(itr != strategies.end()) {
		delete (*itr);
		++itr;
	}
	//strategies.clear();

	redorb.clear();
	if(redorbEx.size() > 0) {
		std::list<ExplodingSprite*>::iterator it = redorbEx.begin();
		while(it != redorbEx.end()) {
			delete (*it);
			++it;
		}
		redorbEx.clear();
	 }
}

Manager::Manager() :
	CompositeManager(),
  env( SDL_putenv(const_cast<char*>("SDL_VIDEO_CENTERED=center")) ),
	helpFlag(false),
  gdata( Gamedata::getInstance() ),
  io( IOManager::getInstance() ),
  clock( Clock::getInstance() ),
	bullets(BulletFactory::getInstance()),
	screen( io.getScreen() ),
  backSurface( io.loadAndSet(gdata->getXmlStr("back"), false) ),
  world(new Frame(backSurface,
                gdata->getXmlInt("viewWidth"), 
                gdata->getXmlInt("viewHeight"), 0, 0),2 ),
	bgSurface( io.loadAndSet(gdata->getXmlStr("bgImage"), false) ),
	bgworld(new Frame(bgSurface,
								gdata->getXmlInt("bgWidth"),
								gdata->getXmlInt("bgHeight"),
								gdata->getXmlInt("bgSrcX"),
								gdata->getXmlInt("bgSrcY"))),
  viewport( Viewport::getInstance() ),
	sp(new SpriteManager()),
	hero(sp->getHero()),
	strategies(),
	collisionStrategy( NULL ),
	redorb(),
	redorbEx(),
	currentObject(0),
	sound()
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    throw string("Unable to initialize SDL: ");
  }
	for(int i = 0 ; i < gdata->getXmlInt("spriteCount") ; i++)
	redorb.push_back(sp->getPerson());
	viewport.setObjectToTrack(hero);
	strategies.push_back( new RectangularCollisionStrategy );
	strategies.push_back( new MidPointCollisionStrategy );
	strategies.push_back( new PerPixelCollisionStrategy );

	collisionStrategy = strategies[2];

//  viewport.setObjectToTrack(redorb[currentObject]);
  atexit(SDL_Quit);
}

void Manager::draw() const {
  world.draw();
	bgworld.draw();
	hero->draw();
	bullets.draw();
	if(redorbEx.size() > 0) {
		std::list<ExplodingSprite*>::const_iterator itr = redorbEx.begin();
		while(itr != redorbEx.end()) {
			(*itr)->draw();
			++itr;
		}
	}
	if(redorb.size() > 0) {
		std::vector<Drawable*>::const_iterator itr = redorb.begin();
		while(itr != redorb.end()) {//redorbEx.size() > 0) {
			(*itr)->draw();
			++itr;
		}
	}

	if(helpFlag) {
		io.printMessageAt("Help Screen",200,200);
		io.printMessageAt("Tracking :"+ redorb[currentObject]->getName(),200,220);
		io.printMessageAt("Press F1 to resume the game",200,240);
		io.printMessageAt("Press t to track different objects",200,260);
		io.printMessageAt("Press p to pause the game", 200, 280);
	}
}

void Manager::update(Uint32 ticks) {
	viewport.update();
	world.update();
	hero->jumpUpdate(ticks);
	bullets.update(ticks);
	bgworld.update();
	if(redorb.size() > 0) {
		std::vector<Drawable*>::iterator it = redorb.begin();
		while(it != redorb.end()) {
			(*it)->update(ticks);
			++it;
		}
	}
	if(redorbEx.size() > 0) {
		std::list<ExplodingSprite*>::iterator it = redorbEx.begin();
		while(it != redorbEx.end()) {//redorbEx.size() > 0) {
			(*it)->update(ticks);
			if((*it)->chunkCount() == 0) {
				delete (*it);
				it = redorbEx.erase(it);
			}
			++it;
		}
	}
}

void Manager::checkForCollision() {
std::vector<Drawable*>::iterator sprite = redorb.begin();
std::list<Sprite*>& li = bullets.getBulletList();
std::list<Sprite*>::iterator i = li.begin();
while(i != li.end()) {
	while(sprite != redorb.end()) {
		if ( collisionStrategy->execute(*(*i), *(*sprite) )) { 
			redorbEx.push_back(new ExplodingSprite(*(static_cast<Sprite*>(*sprite))));
			sprite = redorb.erase(sprite);
			sound[6];
			break;
		} else {
			++sprite;
		}
	}
	++i;
} 
}

Manager::MODE Manager::play() {
SDL_Event event;
bool done = false;
bool keyCatch = false;
while ( not done ) {
  draw();
  SDL_Flip(screen);
  Uint32 ticks = clock.getElapsedTicks();
  update(ticks);
	checkForCollision();
	SDL_PollEvent(&event);
    if (event.type == SDL_QUIT) { break; }
    if(event.type == SDL_KEYUP) { keyCatch = false; }
    if(event.type == SDL_KEYDOWN) {
      switch ( event.key.keysym.sym ) {
        case SDLK_ESCAPE : done = true; break;
        case SDLK_q      : done = true; break;
        case SDLK_t			 :
				 	if(!keyCatch) {
						keyCatch = true;
						currentObject = (currentObject+1)%redorb.size();
						viewport.setObjectToTrack(redorb[currentObject]);
					}
					break;
				case SDLK_z			 :
					hero->shoot(clock.getTicks());
					sound[1];
					break;
				case SDLK_RIGHT  :
					hero->right(ticks);
					break;
				case SDLK_LEFT	 :
					hero->left(ticks);
					break;
				case SDLK_SPACE  :
					hero->jump();
					break;
				case SDLK_F1		 :
					if (!keyCatch) {
						keyCatch = true;
						if(!helpFlag) {
							helpFlag = true;
							clock.pause();
						}	else {
							helpFlag = false;
							clock.unpause();
						}
					}
					break;
        case SDLK_p      :
					if((!keyCatch) && (!helpFlag)) {
						keyCatch = true;
						if(clock.isPaused()) clock.unpause();
						else clock.pause();
					}
          break;
        default          :
					break;
      }
	}
}
}
