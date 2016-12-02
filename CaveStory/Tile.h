#ifndef TILT_H
#define TILT_H
#include "globals.h"
struct SDL_Texture;
class Graphics;

class Tile
{
public:
	Tile();
	Tile(SDL_Texture *tileset, Vector2 size, Vector2 tilesetPosition, Vector2 position);
	void update(int elapsedTime);
	void draw(Graphics &_graphics);
private:
	SDL_Texture *_tileset;
	Vector2 _size;
	Vector2 _tilesetPosition; //where on the tileset the tile is
	Vector2 _position;	//where on the map the tile is
};





#endif