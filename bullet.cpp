#include "bullet.h"

Bullet::Bullet(const Vector2f& pos, const Vector2f$ vel,
				 const string& n, const Frame* fm/*, int dir) : */Sprite(pos,vel,n,Frame* fm)//,
				 //direction(dir)
				 {}

Bullet::Bullet(const Bullet& b) : 
				Sprite(b.getPosition(), b.getVelocity(), b.getMaxVelocity(), b.name)//,
//				direction(b.direction)
				{}

Bullet& Bullet::operand=(const Bullet& rhs) {
	setName(rhs.getName());
	setPosition(rhs.getPosition());
	setVelocity(rhs.getVelocity);
	frame = rhs.frame;
//	direction = rhs.direction;
}
