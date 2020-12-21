#pragma once
#include "RKEngine.h"

#include "ParticleSystem.h"

namespace Rocket {
    class Sandbox2D : implements Application
    {
    public:
        Sandbox2D() {}
        virtual ~Sandbox2D() = default;

        virtual void PreInitialize() override;
        virtual void PreInitializeModule() override;
    };

    struct ProfileResult_
	{
		const char* Name;
		float Time;
	};

    class Sandbox2DLayer : implements Layer
    {
    public:
        Sandbox2DLayer() : Layer("Sandbox2DLayer") {}
        virtual ~Sandbox2DLayer() = default;

        virtual void OnAttach() override;
		virtual void OnDetach() override;

        virtual void OnUpdate(Timestep ts) override;
        virtual void OnGuiRender() override;
        virtual void OnEvent(Event &event) override;
    private:
        void DrawQuads();
        void DrawMap();
        void DockSpace();
    private:
        OrthographicCameraController* m_Controller;

        std::vector<Ref<Texture2D>> m_Texture;
        glm::vec3 m_SquareColor = { 1.0f, 0.5f, 0.2f };

        std::vector<ProfileResult_> m_ProfileResults;

        std::unordered_map<char, Ref<SubTexture2D>> m_TextureMap;

        ParticleProps m_EngineParticle;
	    ParticleSystem m_ParticleSystem;
        glm::vec2 m_Position = { 0.0f, 0.0f };
        glm::vec2 m_Velocity = { 0.0f, 0.0f };
    };
}