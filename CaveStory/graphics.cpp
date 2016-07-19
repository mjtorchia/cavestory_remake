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
