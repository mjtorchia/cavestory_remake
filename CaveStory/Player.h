#ifndef PLAYER_H
#define PLAYER_H
#include "animatedsprite.h"
#include "globals.h"
class Graphics;

class Player :public AnimatedSprite
{
public:
	Player();
	Player(Graphics &_graphics, Vector2 spawnPoint);
	void draw(Graphics &_graphics);
	void update(float elapsedTime);
	
	/*void moveLeft
	* Moves the player left by -dx
	*/
	void moveLeft();
	
	/*void moveRight
	* Moves the player right by +dx
	*/
	void moveRight();
	
	/*void stopMoving
	* Stops moving the player and plays idel animations based on current direction
	*/
	void stopMoving();

	virtual void animationDone(std::string currentAnimations);
	virtual void setupAnimation();

	void handleTileCollision(std::vector<Rectangle> &others);

	//getter functions
	const float getX() const;
	const float getY() const;

private:
	float _dx, _dy; //change in x and change in y
	Direction _facing;
	bool _grounded; //true if on ground, false if in the air or falling

};



















#endif