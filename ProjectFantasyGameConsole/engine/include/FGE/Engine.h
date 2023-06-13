#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "core.h"
#include "GameObject.h"
#include "ImageObject.h"
#include "Renderer.h"
#include "Window.h"

namespace FGE
{
    typedef std::shared_ptr<GameObject> GameObjectPtr;
	//
	//  typedef std::unique_ptr<Window> WindowPtr;
    typedef std::unique_ptr<EngineRenderer> EngineRendererPtr;
    typedef std::map<std::string, GameObjectPtr> ObjMap;

	class Engine
	{
	private:
		// Engine state
		bool m_EngineActive;
		bool m_SdlInitialized;

	private: // Member variables
		ObjMap m_Objects;
		EngineRendererPtr m_Renderer;

	private: // Object internal methods
		bool ObjectExists(std::string const objName);
		bool IsObjectActive(std::string const objName);
		GameObjectPtr GetObject(std::string const objName);

	private: // Private Renderer Methods
	public:  // Renderer Methods
		void RenderObject(std::string const objName);
	public:
		// Instantiation
		Engine();
		Engine(WindowConfig cfg);
		virtual ~Engine();
	public:
		// Object handling
		void SetObjectActive(std::string const objName);
		bool CreateObject(ObjectType const eObjType, std::string const objName, int const x = 0, int const y = 0);
		bool AttachTextureToObj(std::string const objName, std::string const RscPath);
	public:
		// Handle events
		bool OnEvent(); // Switch statement location xy(z). Check collision with objects. Check bound events. Do overloaded events
		//If then trigger Events from Object class
	};


}

