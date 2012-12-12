#ifndef DRAWABLE__H
#define DRAWABLE__H
#include <SDL.h>
#include <iostream>
#include <string>
using std::string;

#include "vector2f.h"
#include "frame.h"
#include "gamedata.h"
//#include "viewport.h"

//class Viewport;
// Drawable is an Abstract Base Class (ABC) that
// specifies the methods that derived classes may
// and must have.
class Drawable {
public:
  Drawable(const Vector2f& pos, const Vector2f& vel, const Vector2f& mxv, const string& n) : 
    position(pos), velocity(vel), maxVelocity(mxv), name(n) {}

  Drawable(const Drawable& s) : position(s.position), velocity(s.velocity),
    maxVelocity(s.maxVelocity), name(s.name) { }

  virtual ~Drawable() {}//std::cout<<"drawable destructor"<<std::endl;}

  virtual void draw() const = 0;
  virtual void update(Uint32 ticks) = 0;

  float X() const { return position[0]; }
  void X(float x) { position[0] = x; }

  float Y() const { return position[1]; }
  void Y(float y) { position[1] = y; }

  float velocityX() const { return velocity[0]; }
  void velocityX(float vx) { velocity[0] = vx; }

  float velocityY() const { return velocity[1]; }
  void velocityY(float vy) { velocity[1] = vy; }

  const Vector2f& getPosition() const { return position; }
  const Vector2f& getVelocity() const { return velocity; }
  const Vector2f& getMaxVelocity() const { return maxVelocity; }
  void setPosition(const Vector2f& pos) { position = pos; }
  void setVelocity(const Vector2f& vel) { velocity = vel; }
  void setMaxVelocity(const Vector2f& vel) { maxVelocity = vel; }
	virtual void setName(const string&) = 0;


	virtual const Frame* getFrame() const = 0; 
	virtual const string& getName() const = 0;

	virtual unsigned getPixel(Uint32, Uint32) const=0;
private:
  Vector2f position;
  Vector2f velocity;
  Vector2f maxVelocity;
protected:
	string name;	
};
#endif
