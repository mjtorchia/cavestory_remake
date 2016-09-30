#ifndef LEVEL_H
#define LEVEL_H
#include "globals.h"
#include <string>

class Graphics;
struct SDL_Texture; //had to change from class to struct. not sure why

class Level
{
public:
	Level();
	Level(std::string mapName, Vector2 spawnPoint, Graphics &_graphics);	//spawnPoint is where we want the player to spawn on the map
	~Level();
	void update(int elapsedTime);
	void draw(Graphics &_graphics);
private:
	std::string _mapName;
	Vector2 _spawnPoint;
	Vector2 _size;	//width and height of entire map
	SDL_Texture* _backgroundTexture;

	/* void loadMap
	* loads a map
	*/
	void loadMap(std::string mapName, Graphics &_graphics);
};














#endif