#ifndef SPRITE_H
#define SPRITE_H

class Sprite{
	Sprite();
	Sprite(Graphics &_graphics, const std::string &filePath, int sourceX, int SourceY, int width, int height,
		float posX, float posY);
	virtual ~Sprite();
	virtual void update();
};

#endif