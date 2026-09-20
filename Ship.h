#pragma once
#include "Rigidbody.h"

// ============================================================================
// Ship : public Rigidbody
// ----------------------------------------------------------------------------
// The player's ship. Inherits the physics from Rigidbody and adds a thrust
// value and a sprite id. Overrides Simulate() to read the keyboard, and
// overrides Collide() to reset itself when it hits an Asteroid.
// ============================================================================
class Ship : public Rigidbody
{
public:
    Ship();
    ~Ship() override;

    // Override: apply thrust on SPACE, rotate on left/right arrows,
    // then run the base physics.
    void Simulate(float timeStep) override;

    // Override: if 'other' is an Asteroid, reset position/velocity/rotation.
    void Collide(Rigidbody* other) override;

    // Must implement the pure virtual from Rigidbody.
    void Draw() override;

private:
    void Reset();   // put the ship back to the centre, stationary

    float m_thrust   = 500.0f;  // acceleration applied while thrusting
    int   m_spriteId = 0;       // Play::GetSpriteId("ship")
};
