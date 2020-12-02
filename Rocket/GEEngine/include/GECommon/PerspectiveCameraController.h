#pragma once
#include "GECommon/PerspectiveCamera.h"
#include "GECommon/CameraController.h"
#include "GEEvent/KeyEvent.h"
#include "GEEvent/MouseEvent.h"
#include "GEEvent/ApplicationEvent.h"

namespace Rocket {
    class PerspectiveCameraController : implements CameraController
	{
	public:
		PerspectiveCameraController(float aspectRatio, float fov = 45.0f, bool rotation = false);

		virtual void OnUpdate(Timestep ts) override;
		virtual void OnEvent(Event& e) override;

		void OnResize(float width, float height);

		virtual Camera& GetCamera() override { return m_Camera; }
		virtual const Camera& GetCamera() const override { return m_Camera; }

		float GetZoomLevel() const { return m_ZoomLevel; }
		void SetZoomLevel(float level) { m_ZoomLevel = level; }
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
	private:
		float m_AspectRatio;
		float m_ZoomLevel = 45.0f;
		PerspectiveCamera m_Camera;

		bool m_Rotation;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f; //In degrees, in the anti-clockwise direction
		float m_CameraTranslationSpeed = 1e-8f, m_CameraRotationSpeed = 1.0f;
	};
}