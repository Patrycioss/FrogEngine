#include "Camera.hpp"
#include "Engine.hpp"

fe::Camera::Camera() : Zoom(1.0f) {}
fe::Camera::Camera(float _zoom) : Zoom(_zoom) {}

glm::mat4 fe::Camera::GetProjectionMatrix() const {
  float left = 0;
  float right = Engine::CurrentSettings.windowWidth;
  float bottom = Engine::CurrentSettings.windowHeight;
  float top = 0;

  glm::mat4 orthographicMatrix = glm::ortho(left, right, bottom, top, NearPlane, FarPlane);
  glm::mat4 zoomMatrix = glm::scale(glm::mat4(1.0f), {Zoom, Zoom, Zoom});

  return orthographicMatrix * zoomMatrix;
}
