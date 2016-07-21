#include "sprite.h"
#include "graphics.h"
#include "globals.h"

Sprite::Sprite(){}

//sourceX and SourceY are where to start drawing from on the sprite sheet and
//height and width are how many pixels we want to draw
Sprite::Sprite(Graphics &_graphics, const std::string &filePath, int sourceX,
	int sourceY, int width, int height, float posX, float posY): _x(posX),_y(posY){
	
	this->_sourceRect.x = sourceX;
	this->_sourceRect.y = sourceY;
	this->_sourceRect.w = width;
	this->_sourceRect.h = height;

	//Functions needs Renderer which we get from the graphics class and a SDL_Surface which we also
	//call from the graphics class. Refer to graphics class for comments on getRenderer and loadImage
	this->_spriteSheet = SDL_CreateTextureFromSurface(_graphics.getRenderer(), _graphics.loadImage(filePath));
	if (this->_spriteSheet == NULL){
		printf("\nError: Unable to load image\n");
	}
}

Sprite::~Sprite(){}


//Need to use blitsurface functions so we'll need a destinationRectangle
void Sprite::draw(Graphics &_graphics, int x, int y){

	/*where on the screen we'll be drawing
	We multiply the sourceRect width and height by SPRITE_SCALE because we want the sprite to
	be scaled up when it is drawn to the screen. Without multiplying, the sprite that get printed
	to the screen is too small*/
	SDL_Rect destinationRectangle = { x, y, this->_sourceRect.w*globals::SPRITE_SCALE, this->_sourceRect.h*globals::SPRITE_SCALE };
	
	
	_graphics.blitSurface(this->_spriteSheet, &this->_sourceRect, &destinationRectangle);
}

void Sprite::update(){}