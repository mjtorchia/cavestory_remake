#include "Player.h"
#include "graphics.h"

namespace player_constants
{
	const float WALK_SPEED = 0.2f;
	const float GRAVITY = 0.002f;
	const float GRAVITY_CAP = 0.8f;
}

Player::Player()
{
	
}

Player::Player(Graphics &_graphics, Vector2 spawnPoint) : AnimatedSprite(_graphics, "MyChar.png", 0, 0, 16, 16, spawnPoint.x, spawnPoint.y, 100), _dx(0), _dy(0), _facing(RIGHT), _grounded(false)
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

const float Player::getX()const
{
	return this->_x;
}
const float Player::getY()const
{
	return this->_y;
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

//void handleTileCollisions
//handles collisions with all tiles the player is colliding with
void Player::handleTileCollision(std::vector<Rectangle> &other)
{
	//figure out what side the collision happened on and move the player accordingly
	for (int i = 0; i < other.size(); i++)
	{
		sides::Side collisionSide = Sprite::getCollisionSide(other.at(i));
		if (collisionSide != sides::NONE)
		{
			switch (collisionSide)
			{
			case sides::TOP:
				this->_y = other.at(i).getBottom() + 1; /*if the top collides, get the value of the collision rectangle at the bottom\
														and then set the players y value to that. this gives the illusion of collision because
														the player will go through the collision rectangle 1 px and this will set it exactly to where
														it collided keeping it from going through*/
				this->_dy = 0; //this resets all gravity because we hit something. there is no change is y anymore
				break;
			case sides::BOTTOM:
				this->_y = other.at(i).getTop() - this->_boundingBox.getHeight() - 1; /*same idea as above except we need to minus the players height
																					  because if we didnt the players head would end up getting set to the top
																					  of the collision rectangle which would be the player in the rectangle. so if we
																					  subtract the players height it will then place the player on top of the collision rectangle*/
				this->_dy = 0; //reset all gravity because there is no change in y anymore
				break;
			case sides::LEFT:
				this ->_x = other.at(i).getRight() + 1;
				break;
			case sides::RIGHT:
				this->_x = other.at(i).getLeft() - this->_boundingBox.getWidth() - 1;

			}												
		}
	}
	
}
void Player::update(float elapstedTime)
{
	//apply gravity
	if (this->_dy <= player_constants::GRAVITY_CAP)//if change in y pos less than equal to grav cap, then increase gravity cuz we're not falling at the cap yet
	{
		this->_dy += player_constants::GRAVITY*elapstedTime; //as time goes on, "more gravity" will be applied to the player
	}

	//move by dx
	this->_x += this->_dx*elapstedTime;
	//move by dy
	this->_y += this->_dy*elapstedTime;

	AnimatedSprite::update(elapstedTime);
}

void Player::draw(Graphics &_graphics)
{
	AnimatedSprite::draw(_graphics, this->_x, this->_y);
}