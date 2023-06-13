#include <iostream>

#include "_Window.h" // Private headers
#include "_Renderer.h"
#include "_GameObject.h"
#include "_ImageObject.h"
#include "Engine.h"

namespace FGE
{
	Engine::Engine() : m_EngineActive{true}, m_SdlInitialized{ true }
	{
		// Do Setup
		std::cout << "Hello from Engine" << std::endl;
		m_Renderer = std::make_unique<EngineRenderer>(EngineRenderer());
	}
	Engine::Engine(WindowConfig cfg) : m_EngineActive{ true }, m_SdlInitialized{ true }
	{
		// Do Setup
		std::cout << "Hello from Engine" << std::endl;
		m_Renderer = std::make_unique<EngineRenderer>(EngineRenderer(cfg));

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
				ObjectType type = scnd->Type();
				switch (type)
				{
					case IMAGE:
					{
						if (m_Renderer->RenderObject(dynamic_cast<ImageObject*>(scnd.get())))
						{
							// Rendered object successfully.
							std::cout << "Rendered object successfully.\n";
						}
						break;
					}
					default:
					{
						// Log: not supported yet
						break;
					}
				}
				
			}
			// Log: object name x is either not renderable or inactive.
			std::cout << "object is either not renderable or inactive..\n";
		}
		// Log: object not found
	}
	bool Engine::ObjectExists(std::string const objName)
	{
		return m_Objects.find(objName) == m_Objects.end() ? true : false;
	}
	GameObjectPtr Engine::GetObject(std::string const objName)
	{
		auto obj = m_Objects.find(objName);
		return obj->second;
	}
	void Engine::SetObjectActive(std::string const objName)
	{
		if (ObjectExists(objName))
		{
			GameObjectPtr obj = GetObject(objName);
		}
	}
	bool Engine::CreateObject(ObjectType const eObjType, std::string const objName, int const x, int const y)
	{
		if(ObjectExists(objName))
		{
			// Add log
			return false;
		}

		// Make object based on type
		switch (eObjType)
		{
			case IMAGE:
			{
				ImageObject imgObj;

				m_Objects.emplace(objName, std::make_shared<GameObject>(imgObj));
				break;
			}
			default:
			{
				// Log: not supported yet
				return false;
			}
		}
		if (ObjectExists(objName))
		{
			return true;
		}
		// Add log
		return false;
	}
	

}
