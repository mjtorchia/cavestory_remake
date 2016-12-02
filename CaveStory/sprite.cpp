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
	this->_boundingBox = Rectangle(this->_x, this->_y, width*globals::SPRITE_SCALE, height*globals::SPRITE_SCALE);
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

void Sprite::update()
{
	//keeps the bounding box around the players sprite
	this->_boundingBox = Rectangle(this->_x, this->_y, this->_sourceRect.w*globals::SPRITE_SCALE, this->_sourceRect.h*globals::SPRITE_SCALE);
}

const Rectangle Sprite::getBoundingBox()const
{
	return this->_boundingBox;
}

//Side getCollisionSide
//Determine which side the collision happened on
const sides::Side Sprite::getCollisionSide(Rectangle &other)const
{
	//the one with the lowest amount will be which side it is colliding on
	int amtRight;
	int amtLeft;
	int amtTop;
	int amtBottom;
	amtRight = this->getBoundingBox().getRight() - other.getLeft();
	amtLeft = other.getRight() - this->getBoundingBox().getLeft();
	amtTop = other.getBottom() - this->getBoundingBox().getTop();
	amtBottom = this->getBoundingBox().getBottom() - other.getTop();

	//array used to figure out which one is largest
	int vals[4] = { abs(amtRight), abs(amtLeft), abs(amtTop), abs(amtBottom) };
	int lowest = vals[0];
	for (int i = 0; i < 4; i++)
	{
		if (vals[i] < lowest)
		{
			lowest = vals[i];
		}
	}
	return
		lowest == abs(amtRight) ? sides::RIGHT :
		lowest == abs(amtLeft) ? sides::LEFT :
		lowest == abs(amtTop) ? sides::TOP :
		lowest == abs(amtBottom) ? sides::BOTTOM :
		sides::NONE;
}