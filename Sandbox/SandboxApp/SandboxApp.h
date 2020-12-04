#pragma once
#include "RKEngine.h"

#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

extern float vertices[9];
extern uint32_t indices[3];
extern float square_vertices[20];
extern uint32_t square_indices[6];
extern float cube_vertices[180];
extern uint32_t cube_indices[36];

namespace Rocket
{
    class SimpleSandbox : implements Application
    {
    public:
        SimpleSandbox() {}
        virtual ~SimpleSandbox() = default;

        virtual int Initialize() override;
    };
}
