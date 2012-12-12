#include <iostream>
#include <cmath>
#include "multiFrameSprite.h"
#include "gamedata.h"

const int NUMBER_FRAMES = 3;
const int FRAME_INTERVAL = 5;

const Vector2f WALL_LEFT = Vector2f(-1, 0);
const Vector2f WALL_RIGHT = Vector2f(1, 0);
const Vector2f WALL_TOP = Vector2f(0, 1);
const Vector2f WALL_BOTTOM = Vector2f(0, -1);

MultiFrameSprite::MultiFrameSprite(const Vector2f& pos, const Vector2f& vel, 
               const string& n, const vector<Frame*> & fm) :
  Drawable(pos, vel, 
           Vector2f(Gamedata::getInstance()->getXmlInt(n+"MaxXspeed"),
                    Gamedata::getInstance()->getXmlInt(n+"MaxYspeed")),
  n), 
	//name(n),
  frames(fm),
	dt(0),
	currentFrame(0),
	frameChange(0),
 	numberOfFrames( NUMBER_FRAMES ),
	frameInterval( FRAME_INTERVAL )
 { }

MultiFrameSprite::MultiFrameSprite(const MultiFrameSprite& s) :
  Drawable(s.getPosition(), s.getVelocity(), s.getMaxVelocity(), s.name),
  //name( s.getName() ),
  frames(s.frames),
	dt(s.dt),
	currentFrame(s.currentFrame),
	frameChange(0),
 	numberOfFrames( NUMBER_FRAMES ),
	frameInterval( FRAME_INTERVAL )
{ }

void MultiFrameSprite::advanceFrame(Uint32 ticks) {
	float ms = 1000.0/frameInterval;
	dt += ticks;
	int df = dt / ms;
	dt -= df * ms;
	currentFrame = (currentFrame + df) % numberOfFrames;
	currentFrame = currentFrame + (frameChange*numberOfFrames);
}

void MultiFrameSprite::draw() const {						 
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
	//std::cout<<x<<'\t'<<y<<std::endl;
	frames[currentFrame]->draw(x,y);
}

int MultiFrameSprite::getDirection() {
	if(currentFrame < numberOfFrames)
		return 1;
	else
		return 0;
}

void MultiFrameSprite::update(Uint32 ticks) { 
	advanceFrame(ticks);
  float incr = velocityY() * static_cast<float>(ticks) * 0.001;
  Y( Y()+incr );
  float height = static_cast<float>(frames[currentFrame]->getHeight());
  if ( Y() < 0) {
    velocityY( abs( velocityY() ) );
  }
  if ( Y() > Gamedata::getInstance()->getXmlInt("worldHeight")-height) {
    velocityY( -abs( velocityY() ) );
  }

  incr = velocityX() * static_cast<float>(ticks) * 0.001;
  X( X()+incr );
  float width = static_cast<float>(frames[currentFrame]->getWidth());
  if ( X() < 0) {
    velocityX( abs( velocityX() ) );
		frameChange = 0;
  }
  if ( X() > Gamedata::getInstance()->getXmlInt("worldWidth")-width) {
    velocityX( -abs( velocityX() ) );
		frameChange = 1;
  }  
}

unsigned MultiFrameSprite::getPixel(Uint32 i, Uint32 j) const {
	Uint32 x = static_cast<Uint32>(X());
	Uint32 y = static_cast<Uint32>(Y());
	
	x = i - x;
	y = j - y;

	Uint32 *pixels = static_cast<Uint32 *>(frames[currentFrame]->getSurface()->pixels);
	return pixels[ (y * frames[currentFrame]->getWidth()) + x ];
}
