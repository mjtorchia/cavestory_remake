#ifndef GAME_H
#define GAME_H
#include "Player.h"
#include "level.h"

//forward delcare Graphics
class Graphics;

class Game{
public:
	Game();
	~Game();
private:
	void gameLoop();
	void draw(Graphics &graphics);
	void update(float elapsedTime);

	Player _player;
	Level _level; 
};


#endif