#pragma once
#include "GERender/OrthographicCamera.h"
#include "GECommon/CameraController.h"
#include "GEEvent/KeyEvent.h"
#include "GEEvent/MouseEvent.h"
#include "GEEvent/ApplicationEvent.h"

namespace Rocket {
    class OrthographicCameraController : implements CameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);

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
		float m_ZoomLevel = 1.0f;
		OrthographicCamera m_Camera;

		bool m_Rotation;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f; //In degrees, in the anti-clockwise direction
		float m_CameraTranslationSpeed = 5.0f, m_CameraRotationSpeed = 180.0f;
	};
}