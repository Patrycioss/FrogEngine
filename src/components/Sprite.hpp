#pragma once

#include "src/core/Component.hpp"
#include "src/data/Texture.hpp"
#include "src/data/Colour.hpp"
#include "src/settings/SpriteSettings.hpp"

namespace fe
{
  class Sprite : public fe::Component {
   private:
	bool makeShape;
	bool show;

   protected:
	
	/**
	 * The settings used to render the sprite.
	 */
	SpriteSettings spriteSettings;

	/**
	 * The texture to use.
	 */
	fe::Texture* texture;

	/**
	 * The offset between the position of the Sprite and the GameObject.
	 * Starts by default as {0,0}.
	 */
	b2Vec2 offset;

	/**
	 * Used to determine the default size of the Sprite.
	 * By default will use the dimensions of the loaded texture.
	 * @return The default size of Sprite sprite.
	 */
	virtual b2Vec2 GetDefaultSize();

	void Start() override;
	void Update(float _deltaTime) override;
	void Render() override;

   public:
	/**
	 * Sprite Constructor.
	 * @param _texture The Texture to render.
	 * @param _size The size of the Sprite. By default it will use the dimensions of the Texture.
	 * @param _makeShape Whether to add a Box2D shape with the size of the Sprite.
	 */
	explicit Sprite(fe::Texture* _texture, bool _makeShape = true, const b2Vec2& _size = {-1, -1});

	/**
	 * Sprite Constructor.
	 * @param _texture The Texture to render.
	 * @param _makeShape Whether to add a Box2D shape with the size of the Sprite.
	 * @remark The size of the Sprite will be the dimensions of the Texture.
	 */
	explicit Sprite(fe::Texture* _texture, bool _makeShape);

	/**
	 * Sprite Constructor.
	 * @param _texture The Texture to render.
	 * @param _size The size of the Sprite. By default it will use the dimensions of the Texture.
	 * @remark Adds a Box2D shape with the size of the Sprite.
	 */
	explicit Sprite(fe::Texture* _texture, const b2Vec2& _size);

	/**
	 * @return The current SpriteSettings. 
	 */
	[[nodiscard]] const SpriteSettings& GetSpriteSettings() const;
	
	/**
	 * Sets the SpriteSettings.
	 * @param _spriteSettings 
	 */
	void SetSpriteSettings(const SpriteSettings& _spriteSettings);
	
	/**
	 * Sets the offset between the position of the GameObject and the Sprite.
	 */
	void SetOffset(const b2Vec2& _offset);
	
	/**
	 * Sets the colour that will be applied on top of the sprite.
	 * If you want the default colours leave it as white.
	 * @param _colour The colour to set it to.
	 */
	void SetColour(const fe::Colour& _colour);
	
	/**
	 * Flips the sprite horizontally.
	 */
	void FlipHorizontal(bool _value);
	
	/**
	 * Flips the sprite vertically.
	 */
	void FlipVertical(bool _value);
	
	/**
	 * Decides whether to show the sprite or not.
	 */
	void Show(bool _value);
  };
}