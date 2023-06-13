#pragma once
#include "_GameObject.h"
#include <string>
namespace FGE 
{
	GameObject::GameObject() :
		m_IsActive{ false }, 
		m_ObjType{ NONE },
		m_Renderable{ false }, 
		m_ResourcePath{ std::string() }
	{	
		FillDefaultRects();
	}
	GameObject::GameObject(ObjectType objType) :
		m_IsActive{ false },
		m_ObjType{ objType },
		m_Renderable{ false },
		m_ResourcePath{ std::string()}
	{
		FillDefaultRects();
	}
	GameObject::GameObject(ObjectType objType, std::string const RscPath) :
		m_IsActive{ false },
		m_ObjType{ objType },
		m_Renderable{ false }
		
	{
		m_ResourcePath = RscPath ;
		FillDefaultRects();
	}
	void GameObject::FillDefaultRects()
	{
		srect.x = 0;
		srect.y = 0;
		srect.w = 0;
		srect.h = 0;

		drect.x = 0;
		drect.y = 0;
		drect.w = 0;
		drect.h = 0;
	}
	bool GameObject::DetermineRenderable(ObjectType const& objType)
	{
		switch (objType)
		{
		case NONE:
		case FONT:
		case AUDIO:
			return false;
		case TEXT:
		case IMAGE:
			return true;
		}
		return false;
	}
	void GameObject::Activate()
	{
		m_IsActive = true;
	}
}
