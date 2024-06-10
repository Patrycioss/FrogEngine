#pragma once

namespace fe
{
  class Engine;
  class Time {
	friend Engine;
	
   public:
	static float GetTimeSeconds();
	
  };
}