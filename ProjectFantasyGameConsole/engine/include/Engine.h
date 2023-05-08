#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
namespace FGE
{
	int const ENUM_RENDERABLE_START = 100; // Defines the minimum number of an enum that will be renderable by the SDL renderer (pictures, text...)
	// Why is this done? When a render function is called, the object needs to be renderable. 
	// You can do this through the bool or through the enum. If the enum is 10 or higher (use const for comparison) then it's renderable.
	// If the user then creates an object, the fact whether it's renderable is solely dependent on ObjectType.
	// Renderable will then not have to be passed in through the constructor
	// This effectively reduces an error source by not letting the user determine whether something is renderable or not.
	// See GameObject constructor in Engine.cpp

	enum ObjectType
	{
		NONE = 0,
		FONT = 1,
		AUDIO = 3,

		TEXTURE = ENUM_RENDERABLE_START, // 100. 
		PICTURE = 101,
	};
	enum EventType
	{
		NONE = 0,
		OnClick = 1,
		OnCollision = 2
	};

	// Notice this is some privisionary architecture. The structure will be vastly different from implementation
	// Once I have a bigger idea


	class Event
	{
	private:
		EventType m_EventType;
	public:
		Event(EventType eEventType) { m_EventType = eEventType; };
	};

	// This class should probably not be the actual object. It should be what different types of object inherit from.
	// So in reality we should have for example a renderable object (like a picture) that inherits from GameObject
	// like a Prop TO DO
	class GameObject
	{
	private:
		ObjectType m_ObjType;
		std::vector<Event> m_Events;
		bool m_IsActive;
		bool m_Renderable;
	private: // Keep them separate for logical view
		Vec2D m_Dimensions;
	public:
		GameObject(ObjectType const objType, int const x = 0, int const y = 0);
		ObjectType Type() { return m_ObjType; }
		bool Renderable() { return m_Renderable; }
		bool Active() { return m_IsActive; }

		// Virtual functions. Add Lua support to adjust what's inside the function or rewrite
		// virtual void OnMouseDown()
		// virtual void OnCollision()

	};

	class Engine
	{
	private:
		// Engine state
		bool m_EngineActive;
		bool m_SdlInitialized;
	private:
		// Member variables
		std::map<std::string, GameObject&> m_Objects;
		Vec2D m_Dimensions;
		// RendererClass m_Renderer;

	private:
		bool ObjectExists(std::string const objName);
		bool IsObjectActive(std::string const objName);
	public:

		Engine();
		virtual ~Engine();
		void RenderObject(std::string const objName);
		void SetObjectActive(std::string const objName);
		bool CreateObject(ObjectType const eObjType, std::string const objName, int const x = 0, int const y = 0);
		//void BindObjectToEvent(std::string const objName, EventType eEventType, void** fnc); // Bind objects to events. Use function pointers to bind event on enter


		// Handle events
		bool OnEvent(); // Switch statement location xy(z). Check collision with objects. Check bound events. Do overloaded events
		//If then trigger Events from Object class
	};

	class Vec2D : Vec
	{
	private:
		// Intentionally not using m_
		int x;
		int y;
	public:
		Vec2D();
		void AdjustVector(int const Addx, int const Addy);
		void SetVector(int const x, int const y);
	};

	class Vec // Interface
	{
	public:
		Vec();
		virtual void AdjustVector(int const Addx, int const Addy) = 0;
		virtual void SetVector(int const x, int const y) = 0;
	};

}