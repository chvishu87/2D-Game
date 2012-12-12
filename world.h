#ifndef WORLD__H
#define WORLD__H

#include "frame.h"
#include "viewport.h"

class World {
public:
  World(Frame* const frame, int fact = 1) : 
      frame1(*frame), frame2(*frame), 
      frameWidth( frame1.getWidth() ),
	  frameHeight( frame1.getHeight() ),
      worldWidth( Gamedata::getInstance()->getXmlInt("worldWidth") ),
	  worldHeight( Gamedata::getInstance()->getXmlInt("worldHeight") ),
      factor(fact),
      viewX(0.0), viewY(0.0), 
      view(Viewport::getInstance()) 
  {}
  void update();
  void draw() const;
private:
  Frame const frame1;
  Frame const frame2;
  unsigned frameWidth;
  unsigned frameHeight;
  unsigned worldWidth;
  unsigned worldHeight;
  int factor;
  float viewX;
  float viewY;
  const Viewport & view;
  World(const World&);
  World& operator=(const World&);
};

#endif
