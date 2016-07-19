#include "graphics.h"
#include <SDL.h>

/*Graphics Class
*Holds all info dealing with graphics for the game
*/

//Constructor
Graphics::Graphics()
{
	
	//initializes the window and renderer to 640x480
	if (SDL_CreateWindowAndRenderer(640, 480, 0, &this->_window, &this->_renderer) < 0)
	{
		cout << "Window Creation Failed" << SDL_GetError();
	};
	
	//sets the title of the window
	SDL_SetWindowTitle(this->_window, "Cavestory");
}

//Destructor
Graphics::~Graphics()
{	
	//Destroys the window
	SDL_DestroyWindow(this->_window);
	SDL_DestroyRenderer(this->_renderer);
}

SDL_Surface* Graphics::loadImage(const std::string &filePath){
	//this checks to see if it can count the number of times filepath
	//is in spritesheets. if its 0 then it hasnt been loaded yet
	if (this->_spriteSheets.count(filePath) == 0){
		//spritesheet @ filePath is equal to the image that you want to load (filePath of the image)
		this->_spriteSheets[filePath] = IMG_Load(filePath.c_str());
	}
	return this->_spriteSheets[filePath];
}

void Graphics::blitSurface(SDL_Texture* texture, SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle){
	//(renderer that we're copying to, texture that we're copying, what part of the texture we're copying, where on the renderer to put it)
	SDL_RenderCopy(this->_renderer, texture, sourceRectangle, destinationRectangle);
}

//Draws content of renderer to screen
void Graphics::flip(){
	SDL_RenderPresent(this->_renderer);
}
//clears content of renderer
void Graphics::clear(){
	SDL_RenderClear(this->_renderer);
}
//getter for renderer
SDL_Renderer* Graphics::getRenderer() const{
	return this->_renderer;
}