#pragma once
#include "GECore/Core.h"
#include "GERender/Texture.h"

#include <glm/glm.hpp>

namespace Rocket
{
    class SubTexture2D
    {
    public:
        SubTexture2D(const Ref<Texture2D> &texture, const glm::vec2 &min, const glm::vec2 max);

        const Ref<Texture2D> GetTexture() { return m_Texture; }
        const glm::vec2 *GetTexCoords() { return m_TexCoords; }

        static Ref<SubTexture2D> Create(const Ref<Texture2D> &texture, const glm::vec2 &coord, const glm::vec2 cellSize, const glm::vec2 spriteSize = {1, 1});

    private:
        Ref<Texture2D> m_Texture;
        glm::vec2 m_TexCoords[4];
    };
} // namespace Rocket