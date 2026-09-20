#include "Rigidbody.h"

// ============================================================================
// Rigidbody definitions live HERE, in the .cpp, NOT in the header.
// The brief is strict about this: declarations (.h) must be separate from
// definitions (.cpp).
// ============================================================================

Rigidbody::Rigidbody(Play::Point2D position, float radius)
    : m_position(position), m_radius(radius)
{
}

Rigidbody::~Rigidbody()
{
}

void Rigidbody::Simulate(float timeStep)
{
    // Default integration step, shared by every body (from the brief's pseudo-code):
    //   position += velocity * timeStep
    //   velocity += acceleration * timeStep
    //   acceleration resets to 0 each frame
    m_position += m_velocity * timeStep;
    m_velocity += m_acceleration * timeStep;
    m_acceleration = { 0.0f, 0.0f };

    // Screen-edge WRAPPING (the "boundary behavior" the brief asks for): an
    // object that leaves one side reappears on the opposite side, like the real
    // Asteroids. This lives in the BASE class so every body (ship AND asteroids)
    // gets it for free through inheritance.
    const float w = static_cast<float>(Play::GetBufferWidth());
    const float h = static_cast<float>(Play::GetBufferHeight());
    if (m_position.x < 0.0f) m_position.x += w;
    if (m_position.x > w)    m_position.x -= w;
    if (m_position.y < 0.0f) m_position.y += h;
    if (m_position.y > h)    m_position.y -= h;
}

void Rigidbody::Collide(Rigidbody* /*other*/)
{
    // Base bodies do nothing on collision. Ship overrides this.
}

bool Rigidbody::IsCollidingWith(const Rigidbody* other) const
{
    if (other == nullptr || other == this)
        return false;

    // Simple circle-vs-circle test: distance between centres < sum of radii.
    Play::Vector2D delta = m_position - other->m_position;
    float distanceSq = delta.x * delta.x + delta.y * delta.y;
    float radii = m_radius + other->m_radius;
    return distanceSq < (radii * radii);
}
