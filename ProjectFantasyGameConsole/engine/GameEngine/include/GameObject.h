#include <iostream>
#include <vector>
#include "Vec.h"
constexpr int ENUM_RENDERABLE_START = 100;
// Defines the minimum number of an enum that will be renderable by the SDL renderer (pictures, text...)
// Why is this done? When a render function is called, the object needs to be renderable. 
// You can do this through the bool or through the enum. If the enum is 10 or higher (use const for comparison) then it's renderable.
// If the user then creates an object, the fact whether it's renderable is solely dependent on ObjectType.
// Renderable will then not have to be passed in through the constructor
// This effectively reduces an error source by not letting the user determine whether something is renderable or not.

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
protected:
	// SDL Types
protected:
	ObjectType m_ObjType;
	std::vector<Event> m_Events; // Events that can be triggered for this object
	bool m_IsActive;
	bool m_Renderable;

// Removed. Not every object will have dimensions. Use Vec2 inheritance to implement
//protected:
	//Vec2D m_Dimensions;
public:
	GameObject(){};
	GameObject(ObjectType const objType);
	ObjectType Type() { return m_ObjType; }
	bool Renderable() { return m_Renderable; }
	bool Active() { return m_IsActive; }

	// Virtual functions. Add Lua support to adjust what's inside the function or rewrite
	// virtual void OnMouseDown()
	// virtual void OnCollision()

	virtual void CheckInteract(GameObject& const other);
};