#pragma once
#include "GECore/Core.h"
#include "GEUtils/Timestep.h"

#include <entt/entt.hpp>

namespace Rocket
{
    class Entity;

	class Scene
	{
	public:
		Scene();
		~Scene();

		Entity CreateEntity(const std::string &name = "");
		void DestroyEntity(Entity entity);

		void OnUpdate(Timestep ts);
		void OnViewportResize(uint32_t width, uint32_t height);

		Entity GetPrimaryCameraEntity();
	private:
		template<typename T>
		void OnComponentAdded(Entity entity, T& component);
	private:
		entt::registry m_Registry;
		uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;

		friend class Entity;
		friend class SceneSerializer;
		friend class SceneHierarchyPanel;
	};
}