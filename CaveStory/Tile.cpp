#include "Tile.h"
#include "graphics.h"
#include <SDL.h>


Tile::Tile()
{
}

Tile::Tile(SDL_Texture *tileset, Vector2 size, Vector2 tilesetPostion, Vector2 position) : _tileset(tileset), _size(size), _tilesetPosition(tilesetPostion), _position(Vector2(position.x*globals::SPRITE_SCALE, position.y*globals::SPRITE_SCALE))
{
	//set values of private variables
}

void Tile::update(int elapsedTime)
{
	
}
void Tile::draw(Graphics &_graphics)
{
	SDL_Rect destRect = { this->_position.x, this->_position.y, this->_size.x*globals::SPRITE_SCALE, this->_size.y*globals::SPRITE_SCALE };
	SDL_Rect sourceRect = { this->_tilesetPosition.x, this->_tilesetPosition.y, this->_size.x, this->_size.y };
	_graphics.blitSurface(this->_tileset, &sourceRect, &destRect);
}

