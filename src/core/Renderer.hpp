#pragma once

#include <vector>

#include "src/data/Texture.hpp"
#include "src/data/Shader.hpp"
#include "src/settings/AnimationSettings.hpp"
#include "src/settings/SpriteSettings.hpp"

namespace fe
{
  class Engine;
  
  /**
   * Contains all functionality for rendering sprites and shapes to the screen.
   */
  class Renderer {
	friend Engine;
   private:
	struct Polygon{
	  std::vector<b2Vec2> vertices{};
	  Colour colour = fe::Colour::WHITE;
	};
	
	static uint32_t spriteVAO;
	
	static ShaderRef spriteShader;
	static ShaderRef shapeShader;
	static ShaderRef animationShader;
	
	static std::vector<Polygon> polygonsToDraw;
	
	// Delete constructors
	Renderer() = delete;
	Renderer(Renderer& _renderer) = delete;
	Renderer(Renderer&& _renderer) = delete;

	static void Initialize();
	static void SetupGLData();
	static void RenderQueued();
	static void Cleanup();

   public:
	/**
	 * Draws a rectangular sprite to the screen.
	 * It is recommended to use a Sprite Component instead of calling this function manually.
	 * @param _texture The texture to use.
	 * @param _spriteSettings The SpriteSettings to use, e.g.: position, rotation...
	 */
	static void DrawSprite(Texture* _texture, const SpriteSettings& _spriteSettings);
	
	/**
	 * Draws a polygon based on vertices to the screen. Mostly used for Box2D debug drawing.
	 * @param _vertices The points that make up the polygon.
	 * @param _vertexCount The amount of points in the polygon.
	 * @param _colour The colour of the polygon.
	 */
	static void DrawPolygon(b2Vec2* _vertices, int _vertexCount, Colour _colour = Colour::WHITE);
	
	/**
	 * Draws an animated sprite based on a sprite sheet to the screen.
	 * It is recommended to use an AnimatedSprite Component instead of calling this function manually.
	 * @param _texture A texture of a sprite sheet.
	 * @param _animationSettings The AnimationSettings to use, e.g.: columns, rows...
	 * @param _spriteSettings The SpriteSettings to use, e.g.: position, rotation...
	 */
	static void DrawAnimationSprite(Texture* _texture, const AnimationSettings& _animationSettings, const SpriteSettings& _spriteSettings);
  };
}