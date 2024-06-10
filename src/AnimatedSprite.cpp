#include "AnimatedSprite.hpp"
#include "Renderer.hpp"
#include "Time.hpp"
#include "GameObject.hpp"

namespace fe
{
  AnimatedSprite::AnimatedSprite(fe::Texture* _texture, const AnimationSettings& _animationSettings, const b2Vec2& _size, bool _makeShape)
	  : Sprite(_texture, _size, _makeShape), animationSettings(_animationSettings) {
  }

  void AnimatedSprite::Render() {
	Renderer::DrawAnimationSprite(texture, animationSettings,
								  {
									  GameObject->GetPosition() + offset,
									  GameObject->GetAngle(),
									  size * GameObject->GetScale(),
									  colour
								  },
								  Time::GetTimeSeconds());
  }

  void AnimatedSprite::SetCycle(int _startFrame, int _frameCount) {
	animationSettings.SetCycle(_startFrame, _frameCount);
  }

  int AnimatedSprite::GetTotalFrameCount() const {
	return animationSettings.totalFrameCount;
  }

  b2Vec2 AnimatedSprite::GetDefaultSize() {
	b2Vec2 textureSize = texture->GetSize();
	return b2Vec2{textureSize.x / (float)animationSettings.columns, textureSize.y / (float)animationSettings.rows};
  }
}