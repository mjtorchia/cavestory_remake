#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "globals.h"


class Rectangle
{
public:
	Rectangle(){}
	Rectangle(int x, int y, int width, int height) :_x(x), _y(y), _width(width), _height(height)
	{
		
	}
	const int getCenterX()const
	{
		return this->_x + this->_width / 2; //returns x pos + half the width; center x pos
	}
	const int getCenterY()const
	{
		return this->_y + this->_height / 2; //same idea as above
	}
	const int getLeft()const
	{
		return this->_x;
	}
	const int getRight()const
	{
		return this->_x + this->_width; //move from left corner all the way over to right (distance of width)
	}
	const int getTop()const
	{
		return this->_y;
	}
	const int getBottom()const
	{
		return this->_y + this->_height;
	}

	const int getWidth()const
	{
		return this->_width;
	}
	const int getHeight()const
	{
		return this->_height;
	}
	const int getSide(const sides::Side side)const
	{
		return
			side == sides::LEFT ? this->getLeft() :
			side == sides::RIGHT ? this->getRight() :
			side == sides::TOP ? this->getTop() :
			side == sides::BOTTOM ? this->getBottom() :
			sides::NONE;
	}

	//bool collidesWith
	//Takes in another rectangel and checks if the two are colliding (the rectangle object we are in and the &other)
	//by checking if the sides overlap
	const bool colidesWith(const Rectangle &other)const
	{
		//see ep10 @23 mins for explaination
		return
			this->getRight() >= other.getLeft() && 
			this->getLeft() <= other.getRight() && 
			this->getTop() <= other.getBottom() && 
			this->getBottom() >= other.getTop();
	}

	const bool isValidRectangle() const
	{
		return(this->_x >= 0 && this->_y >= 0 && this->_width >= 0 && this->_height >= 0);
	}
private:
	int _x;
	int _y;
	int _width;
	int _height;
};








#endif