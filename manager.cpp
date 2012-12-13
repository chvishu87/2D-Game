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
  env( SDL_putenv(const_cast<char*>("SDL_VIDEO_CENTERED=center")) ),
	bitset(0),
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
	//collisionFound( false ),
	redorb(),
	redorbEx(),
	currentObject(0),
	sound(),
	del(false)
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

	collisionStrategy = strategies[1];

//  viewport.setObjectToTrack(redorb[currentObject]);
  //atexit(SDL_Quit);
	clock.pause();
}

void Manager::draw() const {
  world.draw();
	bgworld.draw();
	if(not del)			// take care of it laterr.
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
		unsigned tick = clock.getTicks();
		std::vector<Drawable*>::iterator it = redorb.begin();
		while(it != redorb.end()) {
			(*it)->update(ticks);
			(static_cast<Enemy*>(*it))->shoot(tick, hero->X(), hero->getDirection());
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
std::list<Sprite*>& ili = bullets.getInactiveBulletList();
std::list<Sprite*>::iterator i = li.begin();
while(i != li.end()) {
	bool collisionFound = false;
	while(sprite != redorb.end()) {
		if ( collisionStrategy->execute(*(*i), *(*sprite) )) { 
			redorbEx.push_back( new ExplodingSprite( *(static_cast<Sprite*>(*sprite)) ) );
			sprite = redorb.erase(sprite);
			ili.push_back(*i);
			i = li.erase(i);
			collisionFound = true;
			sound[6];
			break;
		} else {
			++sprite;
		}
	}
	if(!collisionFound)
		++i;
}
/*while( sprite  != redorb.end() ) {
	if( collisionStrategy->execute(*hero, *(*sprite)) ) {
		redorbEx.push_back( new ExplodingSprite( *hero ) );
		del = true;
		//delete hero;
		break;
	} else {
		++sprite;
	}
}*/
}

void Manager::play() {
clock.unpause();
SDL_Event event;

bool done = false;
bool keyCatch = false;
while ( not done ) {
  draw();
  SDL_Flip(screen);
  Uint32 ticks = clock.getElapsedTicks();
	
  update(ticks);
	checkForCollision();
	if(del) {
		done = true;
		break;
	}
	SDL_PollEvent(&event);
    if (event.type == SDL_QUIT) { break; }
    if(event.type == SDL_KEYUP) {
			keyCatch = false; // new code is added after this line.
			switch ( event.key.keysym.sym ) {
        case SDLK_ESCAPE :	break;
        case SDLK_q      :	break;
        case SDLK_t			 :	break;
				case SDLK_z			 :	bitset &= ~(1<<4);	break;
				case SDLK_RIGHT  :	bitset &= ~(1<<5);	break;
				case SDLK_LEFT	 :	bitset &= ~(1<<6);	break;
				case SDLK_SPACE  :	break;
				case SDLK_F1		 :	break;
        case SDLK_p      :	break;
        default          : break;
      } //code is added till here.
		}
    if(event.type == SDL_KEYDOWN) {
			/*std::cout<<event.key.keysym.sym<<'\t'<<SDLK_ESCAPE<<std::endl;
			if( event.key.keysym.sym & SDLK_ESCAPE ) {
				done = true;
				clock.pause();
			}*/
			
			//std::cout<<event.key.keysym.sym<<'\t'<<SDLK_ESCAPE<<std::endl;
      switch ( event.key.keysym.sym ) {
        case SDLK_ESCAPE : bitset |= 1<<1;break;//done = true; clock.pause(); break;
        case SDLK_q      : bitset |= 1<<2;break;//done = true; break;
        case SDLK_t			 :
				 	if(!keyCatch) {
						bitset |= 1<<3;
						//keyCatch = true;
						//currentObject = (currentObject+1)%redorb.size();
						//viewport.setObjectToTrack(redorb[currentObject]);
					}
          break;
				case SDLK_z			 :
					bitset |= 1<<4;
					/*hero->shoot(clock.getTicks());
					sound[1];*/
					break;
				case SDLK_RIGHT  :
					bitset |= 1<<5;
					//hero->right(ticks);
					break;
				case SDLK_LEFT	 :
					bitset |= 1<<6;
					//hero->left(ticks);
					break;
				case SDLK_SPACE  :
					bitset |= 1<<7;
					//hero->jump();
					break;
				case SDLK_F1		 :
					bitset |= 1<<8;
					if (!keyCatch) {
						keyCatch = true;
						/*if(!helpFlag) {
							helpFlag = true;
							clock.pause();
						}	else {
							helpFlag = false;
							clock.unpause();
						}*/
					}
					break;
        case SDLK_p      :
					bitset |= 1<<9;
					if((!keyCatch) && (!helpFlag)) {
						keyCatch = true;
						//if(clock.isPaused()) clock.unpause();
						//else clock.pause();
					}
          break;
        default          : break;
      }
			if(bitset & (1<<1)) { bitset &= ~(1<<1); done = true; clock.pause(); }
			if(bitset & (1<<2)) { bitset &= ~(1<<2); done = true; }
			if(bitset & (1<<3)) {
				bitset &= ~(1<<3);
				currentObject = (currentObject+1)%redorb.size();
				viewport.setObjectToTrack(redorb[currentObject]);
			}
			if(bitset & (1<<4)) { sound[1];hero->shoot(clock.getTicks()); }
			if(bitset & (1<<5)) { hero->right(ticks); }
			if(bitset & (1<<6)) { hero->left(ticks); }
			if(bitset & (1<<7)) { bitset &= ~(1<<7); hero->jump(); }
			if(bitset & (1<<8)) {
				bitset &= ~(1<<8);
				if(!helpFlag) {
					helpFlag = true;
					clock.pause();
				} else {
					helpFlag = false;
					clock.unpause();
				}
			}
			if(bitset & (1<<9)) {
					bitset &= ~(1<<9);
					if(clock.isPaused()) clock.unpause();
					else clock.pause();
				}
		}
	}
}
