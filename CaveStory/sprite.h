#ifndef SPRITE_H
#define SPRITE_H
//#include "graphics.h"
#include <SDL.h>
#include <string>

//forward delcare
class Graphics;

/* Sprite Class
* Holds all information for individual sprites
*/
class Sprite{
public:
	Sprite();
	Sprite(Graphics &_graphics, const std::string &filePath, int sourceX, int SourceY, int width, int height,
		float posX, float posY);

	//Functions will be overwritten in other classes
	virtual ~Sprite();
	virtual void update();
	void draw(Graphics &_graphics, int x, int y);
private:
	SDL_Rect _sourceRect;
	SDL_Texture* _spriteSheet;

	float _x;
	float _y;
};

#endif