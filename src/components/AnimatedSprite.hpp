#pragma once

#include <string>

#include "src/settings/AnimationSettings.hpp"
#include "src/components/Sprite.hpp"

namespace fe
{
  class AnimatedSprite : public Sprite {
   private:
	AnimationSettings animationSettings;

   protected:
	b2Vec2 GetDefaultSize() override;
	void Render() override;

   public:
	/**
	 * Constructs an AnimatedSprite.
	 * @param _texture A Texture of a sprite sheet.
	 * @param _animationSettings The settings to use for the animation.
	 * @param _size The size of the Sprite. By default it will be the dimensions of one frame.
	 * @param _makeShape Whether to add a Box2D shape with the size of the Sprite.
	 */
	AnimatedSprite(fe::Texture* _texture, const AnimationSettings& _animationSettings, const b2Vec2& _size = {-1, -1}, bool _makeShape = true);

	/**
	 * Constructs an AnimatedSprite.
	 * @param _texture A Texture of a sprite sheet.
	 * @param _animationSettings The settings to use for the animation.
	 * @param _makeShape Whether to add a Box2D shape with the size of the Sprite.
	 * @remark The size of the AnimatedSprite will be the dimensions of one frame.
	 */
	AnimatedSprite(fe::Texture* _texture, const AnimationSettings& _animationSettings, bool _makeShape);

	/**
	 * Sets the animation cycle.
	 * @param _startFrame The first frame of the cycle, take note that indexing frames starts at 0.
	 * @param _frameCount The amount of frames that the cycle lasts.
	 */
	void SetCycle(int _startFrame, int _frameCount);

	/**
	 * @return The total amount of frames in the sheet.
	 */
	[[nodiscard]] int GetTotalFrameCount() const;
  };
}