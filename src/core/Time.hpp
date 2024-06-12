#pragma once

namespace fe
{
  class Engine;

  /**
   * Utilities for checking the Game Time.
   */
  class Time {
	friend Engine;

   public:
	
	/**
	 * @return The time in seconds that has elapsed since the game has started. 
	 */
	static float GetTimeSeconds();
  };
}