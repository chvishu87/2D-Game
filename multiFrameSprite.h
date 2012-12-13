#ifndef MULTIFRAMESPRITE__H
#define MULTIFRAMESPRITE__H

//#include <string>
//using std::string;
#include <iostream>
#include <vector>

#include "drawable.h"
//#include "bulletFactory.h"

using std::vector;

//#include "frame.h"

class MultiFrameSprite : public Drawable {
public:
	MultiFrameSprite();
  MultiFrameSprite(const Vector2f& pos, const Vector2f& vel,
         const string& n,const vector<Frame*>&);
  MultiFrameSprite(const MultiFrameSprite& s);
  virtual ~MultiFrameSprite() { }//std::cout<<"multiframe sprite destructor"<<std::endl;   } 
  MultiFrameSprite& operator=(const MultiFrameSprite&);
  virtual const string& getName() const { return name; }
  void setName(const string& n) { name = n; }

  virtual const Frame* getFrame() const { return frames[currentFrame]; }//return (*frame_iterator); }
//  virtual void setFrame(const Frame* f) { frame = f; }
  virtual void draw() const;
	virtual int getDirection();						// returns 1 if sprite is facing right side 0 for left side.
  virtual void update(Uint32 ticks);
	virtual unsigned getPixel(Uint32, Uint32) const;
	//virtual bool inView();
//  unsigned getPixel(Uint32, Uint32) const;

/*  Vector2f getCenter() const { 
    return Vector2f( X()+frame->getWidth()/2, Y()+frame->getHeight()/2 );
  }*/

/*private:
  string name;*/
	//virtual void shoot(int ticks);
protected:
  const vector<Frame *> frames;
//	std::vector<Frame *>::const_iterator frame_iterator;
//  int getDistance(const MultiFrameSprite*) const;
	float dt;
	unsigned currentFrame;
	unsigned frameChange;
	unsigned numberOfFrames;
	unsigned frameInterval;
	//int bulletGap;
	//BulletFactory& bullfacInstance;
	
	void advanceFrame(Uint32 ticks);
};

#endif
