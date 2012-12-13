#ifndef PLAYER__H
#define PLAYER__H

#include "multiFrameSprite.h"
#include "bulletFactory.h"

class Player : public MultiFrameSprite {
public:
	Player();
	Player(const Vector2f& pos, const Vector2f& vel,
			const string& n, const vector<Frame*>&);
	Player(const Player& s);
	virtual ~Player() {}
	Player& operator=(const Player&);
	void jump();
	void jumpUpdate(Uint32);
	void right(Uint32);
	void left(Uint32);
	void shoot(int ticks);
	int life;
private:
	BulletFactory& bullfacInstance;
	int jmp;
	float p_height;
	int bulletGap;
};

#endif
