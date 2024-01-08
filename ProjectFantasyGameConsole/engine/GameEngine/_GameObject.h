#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <Sdl.h>
#include "_Vec.h"
#include "GameObject.h"

namespace FGE 
{

	typedef std::vector<Event> EventVec;
	class Event
	{
	private:
		EventType m_EventType;
	public:
		Event(EventType eEventType) { m_EventType = eEventType; };
	};

	class GameObject: public Vec2D // Vec2D introduces SDL rects
	{
	private:
		bool DetermineRenderable(ObjectType const& objType);
		void FillDefaultRects(); // Sets SDL/Coordinates to 0
	protected:
		ObjectType m_ObjType;
		EventVec m_Events; // Events that can be triggered for this object
		std::string m_ResourcePath;
		bool m_IsActive;
		bool m_Renderable;
		

	public:
		GameObject();
		GameObject(ObjectType objType);
		GameObject(ObjectType objType, std::string const RscPath);

		ObjectType Type() { return m_ObjType; }
		bool Renderable() { return m_Renderable; }
		bool Active() { return m_IsActive; }
		void Activate();

		// Virtual functions. Add Lua support to adjust what's inside the function or rewrite
		// virtual void OnMouseDown()
		// virtual void OnCollision()

		virtual void CheckInteract(GameObject& other) {};
	};
	
}