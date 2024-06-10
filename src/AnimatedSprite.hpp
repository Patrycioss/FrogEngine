#pragma once

#include <string>
#include <vector>

#include "Texture.hpp"
#include "Component.hpp"
#include "AnimationSettings.hpp"

namespace fe{
  class AnimatedSprite : public Component{
   private:
	fe::Texture* texture;
	AnimationSettings animationSettings;
   public:
	AnimatedSprite(const std::string& _filePath, const AnimationSettings& _animationSettings);
	
	void Render() override;
	void SetCycle(int _startFrame, int _frameCount);
	
	[[nodiscard]] int GetTotalFrameCount() const;
  };
}