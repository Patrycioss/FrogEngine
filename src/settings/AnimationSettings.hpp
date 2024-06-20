#pragma once

namespace fe
{
  /**
   * Settings for an AnimationSprite.
   */
  struct AnimationSettings{
	/**
	 * The amount of columns in the sprite sheet.
	 */
	int columns;
	
	/**
	 * The amount of rows in the sprite sheet.
	 */
	int rows;
	
	/**
	 * The total amount of frames in the sprite sheet.
	 */
	int totalFrameCount;
	
	/**
	 * The speed at which the animation plays in frames per second.
	 */
	float fps;
	
	/**
	 * The first frame of the set animation cycle. Indexes from 0, by default set to 0.
	 */
	int cycleStartFrame;
	
	/**
	 * The amount of frames in the animation cycle. By default equal to the totalFrameCount.
	 */
	int cycleFrameCount;
	
	/**
	 * Constructs the AnimationSettings for an AnimatedSprite.
	 * @param _cols The amount of columns in the sprite sheet.
	 * @param _rows The amount of rows in the sprite sheet.
	 * @param _numFrames The amount of frames in the sprite sheet. Defaults to _cols * _rows.
	 */
	AnimationSettings(int _cols, int _rows, int _numFrames = -1){
	  if (_numFrames == -1){
		totalFrameCount = _cols * _rows;
	  }
	  
	  columns = _cols;
	  rows = _rows;
	  fps = 60;
	  cycleStartFrame = 0;
	  cycleFrameCount = totalFrameCount;
	}
	
	/**
	 * Sets the animation cycle.
	 * @param _cycleStartFrame The first frame of the animation cycle. Indexes from 0.
	 * @param _cycleFrameCount The amount of frames in the animation cycle.
	 */
	void SetCycle(int _cycleStartFrame, int _cycleFrameCount){
	  cycleStartFrame = _cycleStartFrame;
	  cycleFrameCount = _cycleFrameCount;
	}
  };
}