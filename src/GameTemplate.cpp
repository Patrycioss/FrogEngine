#include "GameTemplate.hpp"
#include "Engine.hpp"

namespace fe
{
  void GameTemplate::ApplyAllSettings() const {
	Engine::ApplyAllSettings(settings);
  }

  void GameTemplate::ApplySettings(uint8_t _flags) const {
	Engine::ApplySettings(settings, _flags);
  }
}