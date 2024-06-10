#include "AnimatedSprite.hpp"
#include "ResourceManager.hpp"
#include "Renderer.hpp"
#include "Time.hpp"

namespace fe
{
  AnimatedSprite::AnimatedSprite(const std::string& _filePath, const AnimationSettings& _animationSettings)
	  : animationSettings(_animationSettings) {
	texture = ResourceManager::LoadTexture(_filePath);
  }

  void AnimatedSprite::Render() {
	Renderer::DrawAnimationSprite(texture, animationSettings, Time::GetTimeSeconds());
  }

  void AnimatedSprite::SetCycle(int _startFrame, int _frameCount) {
	animationSettings.SetCycle(_startFrame, _frameCount);
  }

  int AnimatedSprite::GetTotalFrameCount() const {
	return animationSettings.totalFrameCount;
  }
}