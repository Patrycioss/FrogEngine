#pragma once

#include <vec2.hpp>
#include <mat4x4.hpp>

#include "Engine.hpp"

namespace fe{
  class Camera {
   public:
	float Zoom;
	float NearPlane = -1.0f, FarPlane = 1.0f;
	
	Camera();
	explicit Camera(float _zoom);
	[[nodiscard]] glm::mat4 GetProjectionMatrix() const;
  };
}


