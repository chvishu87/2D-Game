#include "player.h"
#include "gamedata.h"

Player::Player(const Vector2f& pos, const Vector2f& vel,
			const string& n, const vector<Frame*>& fm) : 
			MultiFrameSprite(pos, vel, n, fm),
			bullfacInstance(BulletFactory::getInstance()),jmp(0),p_height(0),bulletGap(0) {}


Player::Player(const Player& s) :
	MultiFrameSprite(s.getPosition(), s.getVelocity(), s.name, s.frames),
	bullfacInstance(BulletFactory::getInstance()),jmp(0),p_height(0),bulletGap(0) {}

void Player::jump() {
	if(jmp == 0) {
		jmp = 1;
		p_height = Y();
		velocityY(-200);
	}
}

void Player::jumpUpdate(Uint32 ticks) {
	if(jmp == 1) {
		float incr = velocityY() * static_cast<float>(ticks) * 0.001;
		Y( Y()+incr );

		if(Y() <= p_height-100)
			velocityY( abs( velocityY() ) );

		if(Y() >= p_height) {
			Y(p_height);
			velocityY(0);
			jmp = 0;
		}
	}
} 

void Player::right(Uint32 ticks) {
	float incr = velocityX() * static_cast<float>(ticks) * 0.001;
	float width = static_cast<float>(frames[currentFrame]->getWidth());
	if((incr > 0) && ((X()+incr) <=  Gamedata::getInstance()->getXmlInt("worldWidth")-width)) {
		X(X()+incr);
		frameChange = 0;
		advanceFrame(ticks);
	}
}

void Player::left(Uint32 ticks) {
	float incr = velocityX() * static_cast<float>(ticks) * 0.001;
	if((incr > 0) && ((X()-incr) >= 0)) {
		X(X()-incr);
		frameChange = 1;
		advanceFrame(ticks);
	}
}

void Player::shoot(int ticks) {
	//std::cout<<getDirection()<<std::endl;
	//std::cout<<ticks<<'\t'<<(ticks-bulletGap)<<std::endl;
	if((ticks-bulletGap) >= 250) {
		//std::cout<<"inside"<<std::endl; 
		if(getDirection() == 1)
			bullfacInstance.getBullet(X()+30,Y()+20,getDirection());
		else if (getDirection() == 0)
			bullfacInstance.getBullet(X(),Y()+20,getDirection());
		bulletGap = ticks;
	}
}
