#pragma once
#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include "_GameObject.h"
#include "ImageObject.h"

namespace FGE
{
	// Manages its own texture given by the renderer.
	// Passed into the renderer as pointer to access texture and rects

	class ImageObject : public GameObject // Inherits GameObject 
	{
	private:
		SDL_Texture* m_Tex;
		bool m_IsLoaded;
	protected: // Reminder that Vec2D is inherited. Use their functions to adjust inherited rects

	public:
		ImageObject();
		ImageObject(SDL_Texture* texture);
		void ChangeTexture(SDL_Texture* texture);
		//void updateImgProperties(int ImageWidth, int ImageHeight, int ImgPosx, int ImgPosy, int ImageSizeWidth, int ImageSizeHeight);
		void UnloadTexture();
		bool IsLoaded();
		SDL_Texture* GetTexture(); // Dangerous exposure of raw pointer
	};
}
