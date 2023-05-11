#pragma once
#include "GameObject.h"

namespace FGE 
{
	GameObject::GameObject(ObjectType const objType)
	{
		m_ObjType = objType;
		m_Renderable = objType >= ENUM_RENDERABLE_START ? true : false; // If objecttype >= 100 then it's renderable

		// Add log
		// Object created ...
	}

}
