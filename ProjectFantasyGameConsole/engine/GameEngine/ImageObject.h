#pragma once
#include <string>

#include "SDL.h"
#include "SDL_image.h"

#include "GameObject.h"

class ImageObject : FGE::GameObject, Vec2D // Inherits protected and public GO/VEC2
{

public:
	SDL_Texture* tex;
	SDL_Rect srect; // naming?
	SDL_Rect drect;
	ImageObject(SDL_Texture* texture);
	void loadImage(SDL_Texture* texture);
	void updateImgProperties(int ImageWidth, int ImageHeight, int ImgPosx, int ImgPosy, int ImageSizeWidth, int ImageSizeHeight);
private:
	
protected:

};