#ifndef SPRITE__H
#define SPRITE__H

//#include <string>
//using std::string;
#include <iostream>
#include "viewport.h"
#include "drawable.h"
//#include "frame.h"

//class Viewport;

class Sprite : public Drawable {
public:
  Sprite(const Vector2f& pos, const Vector2f& vel,
				 const string& n, const Frame* fm);
  Sprite(const Sprite& s);
  //virtual ~Sprite() { std::cout <<"Sprite destrucotr"<<name<<std::endl; } 
  Sprite& operator=(const Sprite&);

  const string& getName() const { return name; }
  void setName(const string& n) { name = n; }

  virtual const Frame* getFrame() const { return frame; }
  virtual void setFrame(const Frame* f) { frame = f; }

  virtual void draw() const;
  virtual void update(Uint32 ticks);
  virtual unsigned getPixel(Uint32, Uint32) const;

	virtual bool inView();

  Vector2f getCenter() const { 
    return Vector2f( X()+frame->getWidth()/2, Y()+frame->getHeight()/2 );
  }

	//virtual unsigned getPixel(Uint32, Uint32) const;
/*private:
  string name;*/


protected:
  const Frame * frame;
  int getDistance(const Sprite*) const;
};
#endif
