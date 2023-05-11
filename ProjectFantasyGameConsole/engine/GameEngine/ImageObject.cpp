#include "ImageObject.h"

ImageObject::ImageObject(SDL_Texture* texture)
{
    tex = texture;
}

void ImageObject::loadImage(SDL_Texture* texture) {

   //renderer = ren;

   // static SDL_Texture* t = IMG_LoadTexture(renderer, image_path.c_str());
    tex = texture;
}

void ImageObject::updateImgProperties(int ImageWidth, int ImageHeight, int ImgPosx, int ImgPosy, int ImageSizeWidth, int ImageSizeHeight) {

    srect.h = ImageHeight;
    srect.w = ImageWidth;
    srect.x = 0;

    drect.h = ImageSizeHeight;
    drect.w = ImageSizeWidth;
    drect.x = ImgPosx;
    drect.y = ImgPosy;
}

