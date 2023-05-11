#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include  <sdl.h> // Please, why is this not capitalized?
#include "Vec.h"
#include "GameObject.h"
#include "Renderer.h"
#include "WindowManager.h"

namespace FGE
{
	typedef std::shared_ptr<GameObject> GameObjectPtr;
	typedef std::map<std::string, GameObjectPtr> ObjMap;
	class Engine
	{
	private:
		// Engine state
		bool m_EngineActive;
		bool m_SdlInitialized;

	private: // Member variables
		ObjMap m_Objects;
		Vec2D m_Dimensions;
		//EngineRenderer& m_Renderer;
		Window m_Window;

	private: // Object internal methods
		bool ObjectExists(std::string const objName);
		bool IsObjectActive(std::string const objName);

	private: // Window Methods
		Window& CreateEngineWindow();
		Window& CreateEngineWindow(WindowConfig const cfg);

	private: // Renderer Methods

	public:

		Engine();
		Engine(WindowConfig const cfg);
		virtual ~Engine();
		void RenderObject(std::string const objName);
		void SetObjectActive(std::string const objName);
		bool CreateObject(ObjectType const eObjType, std::string const objName, int const x = 0, int const y = 0);

		// Handle events
		bool OnEvent(); // Switch statement location xy(z). Check collision with objects. Check bound events. Do overloaded events
		//If then trigger Events from Object class
	};


}