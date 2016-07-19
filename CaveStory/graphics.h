#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <map>
#include <string>
#include <SDL_image.h>
#include <iostream>
using namespace std;

//forward delcaring. Allows for me to use my pointers below
//even if the SDL.h hasnt been included
struct SDL_Window;
struct SDL_Renderer;



class Graphics
{
public:
	Graphics();
	~Graphics();

	/* SDL_Surface* loadImage
	* Loads an image into the _spriteSheets map if it doesnt already exist
	* As a result each image will only every been loaded once
	* Returns the image from the map regardless of whether or not it was just loaded
	*/
	SDL_Surface* loadImage(const std::string &filePath);

	/* void blitSurface
	* Draws a texture to a certain part of the screen 
	*/
	void blitSurface(SDL_Texture* source, SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle);
	
	/* void flip
	* Renders everything to the screen
	*/
	void flip();

	/* void clear
	* Clears the screen
	*/
	void clear();

	/*SLD_Renderer* getRenderer();
	* getter for Renderer
	*/
	SDL_Renderer* getRenderer() const;

private:
	SDL_Window* _window;	//Creates the window
	SDL_Renderer* _renderer;	//Does all of the drawing to the window

	//This map will hold in memory (in graphics) object every spritesheet we load into the game
	std::map<std::string, SDL_Surface*> _spriteSheets;
};




#endif