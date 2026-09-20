#pragma once
#include "Rigidbody.h"

// ============================================================================
// Asteroid : public Rigidbody
// ----------------------------------------------------------------------------
// Inherits all the physics from Rigidbody and adds: a scale, a rotational
// speed, and a sprite id for drawing. Overrides Simulate() to also spin, and
// implements the required Draw().
// ============================================================================
class Asteroid : public Rigidbody
{
public:
    Asteroid();   // randomizes velocity, scale and spin (see .cpp)
    ~Asteroid() override;

    // Override: do the normal physics AND slowly rotate the asteroid.
    void Simulate(float timeStep) override;

    // Must implement the pure virtual from Rigidbody.
    void Draw() override;

private:
    float m_scale         = 1.0f;   // randomized within reason
    float m_rotationSpeed = 0.0f;   // radians per second, randomized
    int   m_spriteId      = 0;      // Play::GetSpriteId("asteroid")
};
