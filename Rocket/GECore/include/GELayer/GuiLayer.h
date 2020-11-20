#pragma once

#include "GELayer/Layer.h"

namespace Rocket {
    class GuiLayer : public Layer {
    public:
        GuiLayer(const std::string& name = "GuiLayer") : Layer(name) {}
        virtual ~GuiLayer() = default;

        virtual void OnGuiRender() {}
    };
}