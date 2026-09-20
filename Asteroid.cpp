#include "Asteroid.h"

// A small helper for a random float in [min, max].
static float RandRange(float min, float max)
{
    float t = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    return min + t * (max - min);
}

// [INHERITANCE] Forward to the BASE constructor to set the inherited start
// position and collision radius, then fill in the asteroid-only members.
Asteroid::Asteroid()
    // Start in the top-left corner, radius roughly matches the sprite size.
    : Rigidbody(Play::Point2D{ 50.0f, 50.0f }, 40.0f)
{
    // [PlayBuffer API] Look up the auto-loaded data/sprites/asteroid.png sprite.
    m_spriteId = Play::GetSpriteId("asteroid");

    // Randomize velocity within a reasonable amount (m_velocity is INHERITED).
    m_velocity = { RandRange(-100.0f, 100.0f), RandRange(-100.0f, 100.0f) };

    // Randomize the asteroid-only members: scale and spin.
    m_scale         = RandRange(0.5f, 1.5f);
    m_rotationSpeed = RandRange(-2.0f, 2.0f);   // radians / second

    // Keep the INHERITED collision radius roughly in step with the visual scale.
    m_radius = 40.0f * m_scale;
}

Asteroid::~Asteroid()
{
}

// [POLYMORPHISM] Overrides Rigidbody::Simulate(); this version runs for asteroids.
void Asteroid::Simulate(float timeStep)
{
    // [INHERITANCE] Reuse the base physics (position/velocity integration and
    // screen wrapping) - we do NOT rewrite it here.
    Rigidbody::Simulate(timeStep);

    // ...then add the asteroid-specific slow rotation (spins the sprite).
    m_rotation += m_rotationSpeed * timeStep;
}

// [ABSTRACTION] Concrete implementation of the base's pure virtual Draw().
void Asteroid::Draw()
{
    // [PlayBuffer API] DrawSpriteRotated(id, position, frame, angle, scale).
    // Note we pass m_scale here (Ship passes 1.0f) so each asteroid can be a
    // different size - same base contract, different behaviour = polymorphism.
    Play::DrawSpriteRotated(m_spriteId, m_position, 0, m_rotation, m_scale);
}
