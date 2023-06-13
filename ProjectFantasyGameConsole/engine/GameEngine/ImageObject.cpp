#include "_ImageObject.h"
#include "GameObject.h"

namespace FGE 
{

    ImageObject::ImageObject()
    {
        m_ObjType = IMAGE;
        m_Tex = nullptr;
        m_IsLoaded = false;
    }
    ImageObject::ImageObject(SDL_Texture* texture)
    {
        m_ObjType = IMAGE;
        m_Tex = texture;
        m_IsLoaded = true;
    }

    void ImageObject::ChangeTexture(SDL_Texture* texture) 
    {
        m_Tex = texture;
        m_IsLoaded = false;
    }

    void ImageObject::UnloadTexture()
    {
        // Should I be doing this?
        m_Tex = nullptr;
    }

    bool ImageObject::IsLoaded()
    {
        return m_IsLoaded;
    }

    SDL_Texture* ImageObject::GetTexture()
    {
        return m_Tex;
    }



}

