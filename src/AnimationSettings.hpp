#pragma once

namespace fe
{
  struct AnimationSettings{
	int columns;
	int rows;
	int totalFrameCount;
	float fps;
	int cycleStartFrame;
	int cycleFrameCount;
	
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
	
	void SetCycle(int _cycleStartFrame, int _cycleFrameCount){
	  cycleStartFrame = _cycleStartFrame;
	  cycleFrameCount = _cycleFrameCount;
	}
  };
}