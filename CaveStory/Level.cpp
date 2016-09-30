#include "level.h"
#include "graphics.h"
#include <SDL.h>

Level::Level()
{
	
}
//Note to self
//Colon after class declaration means
//Initialising member variables before the body of the constructor executes.
Level::Level(std::string mapName, Vector2 spawnPoint, Graphics &_graphics) :
_mapName(mapName), _spawnPoint(spawnPoint), _size(Vector2(0, 0))
{
	this->loadMap(mapName, _graphics);
}

Level::~Level()
{

}

void Level::loadMap(std::string mapName, Graphics &_grahpics)
{
	//TEMPORARY CODE TO LOAD THE BACKGROUND
	this->_backgroundTexture = SDL_CreateTextureFromSurface(_grahpics.getRenderer(), _grahpics.loadImage("bkBlue.png"));
	this->_size = Vector2(1280, 960);
}

void Level::update(int elaspedTime)
{
	
}
 
void Level::draw(Graphics &_grahpics)
{
	/*The background (bkBlue) is 64x64 and we want the entire image to be our background
	Since the image is smaller than our background we need to loop and draw it multiple times
	to get the desired result*/
	SDL_Rect sourceRect = {0,0,64,64 };
	SDL_Rect destRect;
	for (int x = 0; x < this->_size.x / 64; x++) //(width of level)/64 is how many times this will run
	{
		for (int y = 0; y < this->_size.y / 64; y++) //(length of level)/64 is how many times this will run
		{
			destRect.x = x * 64; //this will have it draw the first time starting at 0 then it will offset by 64 every time
			destRect.y = y * 64;
			destRect.w = 64;
			destRect.h = 64;
			_grahpics.blitSurface(this->_backgroundTexture, &sourceRect, &destRect);
		}
	}
}

