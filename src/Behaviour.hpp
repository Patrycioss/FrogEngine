#pragma once

class Behaviour {
 protected:
  Behaviour() = default;
  
 public:
  Behaviour(Behaviour& other) = default;
  virtual void Start() = 0;
  virtual void Update(float _deltaTime) = 0;
  virtual void Render() = 0;
  virtual ~Behaviour() = default;
};
