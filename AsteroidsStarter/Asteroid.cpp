#include "Asteroid.h"

// A small helper for a random float in [min, max].
static float RandRange(float min, float max)
{
    float t = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    return min + t * (max - min);
}

Asteroid::Asteroid()
    // Start in the top-left corner, radius roughly matches the sprite size.
    : Rigidbody(Play::Point2D{ 50.0f, 50.0f }, 40.0f)
{
    m_spriteId = Play::GetSpriteId("asteroid");

    // Randomize velocity within a reasonable amount.
    m_velocity = { RandRange(-100.0f, 100.0f), RandRange(-100.0f, 100.0f) };

    // Randomize scale and spin within reason.
    m_scale         = RandRange(0.5f, 1.5f);
    m_rotationSpeed = RandRange(-2.0f, 2.0f);   // radians / second

    // Keep the collision radius roughly in step with the visual scale.
    m_radius = 40.0f * m_scale;
}

Asteroid::~Asteroid()
{
}

void Asteroid::Simulate(float timeStep)
{
    // Reuse the base physics (position/velocity integration)...
    Rigidbody::Simulate(timeStep);

    // ...then add the asteroid-specific slow rotation.
    m_rotation += m_rotationSpeed * timeStep;
}

void Asteroid::Draw()
{
    // DrawSpriteRotated is explicitly allowed by the brief.
    Play::DrawSpriteRotated(m_spriteId, m_position, 0, m_rotation, m_scale);
}
