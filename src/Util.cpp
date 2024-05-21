#include "Util.hpp"

#include <glad/glad.h>

void fe::Util::ClearScreen(const glm::vec4& _clearColour) {

  glClearColor(_clearColour.x, _clearColour.y, _clearColour.z, _clearColour.w);
  glClear(GL_COLOR_BUFFER_BIT);
}
