#include "GEScene/Entity.h"

namespace Rocket
{
    Entity::Entity(entt::entity handle, Scene* scene)
		: m_EntityHandle(handle), m_Scene(scene)
	{
	}
}