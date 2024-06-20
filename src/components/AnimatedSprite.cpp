#include "src/components/AnimatedSprite.hpp"
#include "src/core/Renderer.hpp"
#include "src/core/GameObject.hpp"

namespace fe
{
  b2Vec2 AnimatedSprite::GetDefaultSize() {
	b2Vec2 textureSize = texture->GetSize();
	return b2Vec2{textureSize.x / (float)animationSettings.columns, textureSize.y / (float)animationSettings.rows};
  }
  
  AnimatedSprite::AnimatedSprite(fe::Texture* _texture, const AnimationSettings& _animationSettings, const b2Vec2& _size, bool _makeShape)
	  : Sprite(_texture, _makeShape, _size), animationSettings(_animationSettings) {
  }

  AnimatedSprite::AnimatedSprite(fe::Texture* _texture, const AnimationSettings& _animationSettings, bool _makeShape)
	  : Sprite(_texture, _makeShape, {-1, -1}), animationSettings(_animationSettings) {
  }

  void AnimatedSprite::Render() {
	Renderer::DrawAnimationSprite(texture, animationSettings, spriteSettings);
  }

  void AnimatedSprite::SetCycle(int _startFrame, int _frameCount) {
	animationSettings.SetCycle(_startFrame, _frameCount);
  }

  int AnimatedSprite::GetTotalFrameCount() const {
	return animationSettings.totalFrameCount;
  }
}