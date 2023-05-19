#include "Engine.h"
#include "GameObject.h"
#include <iostream>
namespace FGE
{
	Engine::Engine()
	{
		// Do Setup
		std::cout << "Hello from Engine" << std::endl;
		m_Window = std::make_unique<Window>(Window());
	}
	Engine::Engine(WindowConfig const cfg)
	{
		// Do Setup
		std::cout << "Hello from Engine" << std::endl;
		m_Window = std::make_unique<Window>(Window(cfg));
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
			if (scnd->Renderable() && scnd->Active())
			{
				// Do render or whatever
			}
		}
	}
	bool Engine::ObjectExists(std::string const objName)
	{
		return m_Objects.find(objName) == m_Objects.end() ? true : false;
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
		m_Objects.emplace(objName, std::make_shared<GameObject>(eObjType));
		if (ObjectExists(objName))
		{
			return true;
		}
		// Add log
		return false;
	}
	

}
