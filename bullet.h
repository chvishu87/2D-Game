#ifndef BULLET__H
#define BULLET__H

#include "sprite.h"

class Bullet : public Sprite {
public:
	Bullet(const Vector2f& pos, const Vector2f& vel,
				 const string& n, const Frame* fm)//, int dir);
	Bullet(const Bullet& s);
	virtual ~Bullet(){}
	Bullet operator=(const Bullet&);
//protected:
//	int direction;
public:
	bool inView();	// need to implement the functionality
};
