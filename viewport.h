#ifndef VIEWPORT__H
#define VIEWPORT__H
#include "sprite.h"
#include "multiFrameSprite.h"
#include "gamedata.h"
#include "drawable.h"

//class MultiFrameSprite;

class Viewport {
public:
  static Viewport& getInstance();
  ~Viewport() { std::cout << "Blocking the view ..." << std::endl; }
  void update();

  float X() const { return position[0]; }
  void X(float x) { position[0] = x; }
  float Y() const { return position[1]; }
  void Y(float y) { position[1] = y; }

//  void setObjectToTrack(const Sprite *obj);
//	void setObjectToTrack(const MultiFrameSprite *obj);
	void setObjectToTrack(const Drawable *obj);
//  const Sprite* getObjectToTrack() const { return static_cast<Sprite*>objectToTrack; } 

private:
  Gamedata* const gdata;
  Vector2f position;
  unsigned viewWidth;
  unsigned viewHeight;
  unsigned worldWidth;
  unsigned worldHeight;
  Uint16 objWidth;
  Uint16 objHeight;
  
	const MultiFrameSprite *multiFrameObjectToTrack;
//  const Sprite *objectToTrack;
	const Drawable *objectToTrack; 
  Viewport();
  Viewport(const Viewport&);
  Viewport& operator=(const Viewport&);
};
#endif
