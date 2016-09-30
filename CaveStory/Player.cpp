#include "Player.h"
#include "graphics.h"

namespace player_constants
{
	const float WALK_SPEED = 0.2f;
}

Player::Player()
{
	
}

Player::Player(Graphics &_graphics, float x, float y): AnimatedSprite(_graphics, "MyChar.png", 0, 0, 16, 16, x, y, 100)
{
		_graphics.loadImage("MyChar.png");
		this->setupAnimation();
		this->playAnimation("RunRight");
}

void Player::setupAnimation()
{
	this->addAnimation(1, 0, 0, "IdleLeft", 16, 16, Vector2(0, 0));
	this->addAnimation(1, 0, 16, "IdleRight", 16, 16, Vector2(0, 0));
	this->addAnimation(3, 0, 0, "RunLeft", 16, 16, Vector2(0, 0));
	this->addAnimation(3, 0, 16, "RunRight", 16, 16, Vector2(0, 0));
}

void Player::animationDone(std::string currentAnimation)
{
	
}

//these move functions do not actually move the sprite. they just modify _dx. update is what moves the sprite
void Player::moveLeft()
{
	this->_dx = -player_constants::WALK_SPEED;
	this->playAnimation("RunLeft");
	this->_facing = LEFT;
}

void Player::moveRight()
{
	this->_dx = player_constants::WALK_SPEED;
	this->playAnimation("RunRight");
	this->_facing = RIGHT;
}

void Player::stopMoving()
{
	this->_dx = 0;
	this->playAnimation(this->_facing == RIGHT ? "IdleRight" : "IdleLeft");
}

void Player::update(float elapstedTime)
{
	//move by dx
	this->_x += this->_dx*elapstedTime;

	AnimatedSprite::update(elapstedTime);
}

void Player::draw(Graphics &_graphics)
{
	AnimatedSprite::draw(_graphics, this->_x, this->_y);
}