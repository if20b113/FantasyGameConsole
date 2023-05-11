#include "Engine.h"
#include <iostream>
namespace FGE
{
	Engine::Engine()
	{
		// Do Setup
		std::cout << "Hello from Engine" << std::endl;
	}
	Engine::Engine(WindowConfig const cfg)
	{
		// Do Setup
		std::cout << "Hello from Engine" << std::endl;
		Window
	}
	Engine::~Engine()
	{
		// Shut down
	}
	void Engine::RenderObject(std::string const objName)
	{
		auto find = m_Objects.find(objName);
		if (find != m_Objects.end())
		{
			auto scnd = find->second;
			if (scnd.Renderable() && scnd.Active())
			{
				// Do render
			}
		}
	}
	bool Engine::ObjectExists(std::string const objName)
	{
		return m_Objects.find(objName) == m_Objects.end() ? true : false;
	}
	void Engine::CreateEngineWindow()
	{

	}
	void Engine::SetObjectActive(std::string const objName)
	{
		if (ObjectExists(objName))
		{
			SetObjectActive(objName);
		}
	}
	bool FGE::Engine::CreateObject(ObjectType const eObjType, std::string const objName, int const x, int const y)
	{
		if(ObjectExists(objName))
		{
			// Add log
			return false;
		}
		m_Objects.emplace(objName, GameObject(eObjType, x, y));
		if (ObjectExists(objName))
		{
			return true;
		}
		// Add log
		return false;
	}
	GameObject::GameObject(ObjectType const objType, int const x, int const y) : m_IsActive{false}
	{
		m_ObjType = objType;
		m_Renderable = objType >= FGE::ENUM_RENDERABLE_START ? true : false; // If objecttype >= 100 then it's renderable
		m_Dimensions.SetVector(x,y);
		// Add log
		// Object created ...
	}

}
