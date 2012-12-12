#include <cmath>
#include <vector>

#include "drawable.h"
//#include "sprite.h"
//#include "multiFrameSprite.h"

class CollisionStrategy {
public:
  //virtual bool execute(const MultiFrameSprite&, const Sprite&) const = 0;
	virtual bool execute(const Drawable&, const Drawable&) const=0; 
  virtual void draw() const = 0;
  virtual ~CollisionStrategy() {}//std::cout<<"collisionstrategy destructor"<<std::endl;}
};

class RectangularCollisionStrategy : public CollisionStrategy {
public:
  RectangularCollisionStrategy() {}
	virtual bool execute(const Drawable&, const Drawable&) const;	
  //virtual bool execute(const MultiFrameSprite&, const Sprite&) const;
  virtual void draw() const;
};

class MidPointCollisionStrategy : public CollisionStrategy {
public:
  MidPointCollisionStrategy() {}
  virtual bool execute(const Drawable&, const Drawable&) const;
  virtual void draw() const;
  float distance(float, float, float, float) const;
};

class PerPixelCollisionStrategy : public CollisionStrategy {
public:
  PerPixelCollisionStrategy() {}
  virtual bool execute(const Drawable&, const Drawable&) const;
  virtual void draw() const;
};

