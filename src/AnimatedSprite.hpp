#pragma once

#include <string>
#include <vector>

#include "Texture.hpp"
#include "AnimationSettings.hpp"
#include "SpriteSettings.hpp"
#include "Sprite.hpp"

namespace fe{
  class AnimatedSprite : public Sprite{
   private:
	AnimationSettings animationSettings;
	
   protected:
	b2Vec2 GetDefaultSize() override;
	
   public:
	AnimatedSprite(fe::Texture* _texture, const AnimationSettings& _animationSettings, const b2Vec2& _size = {-1,-1}, bool _makeShape = true);
	
	void Render() override;
	void SetCycle(int _startFrame, int _frameCount);
	
	[[nodiscard]] int GetTotalFrameCount() const;
  };
}