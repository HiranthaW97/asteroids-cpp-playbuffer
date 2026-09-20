#include "Ship.h"
#include "Asteroid.h"   // needed for the dynamic_cast in Collide()

Ship::Ship()
    : Rigidbody(Play::Point2D{ 640.0f, 360.0f }, 30.0f)  // centre of a 1280x720 window
{
    m_spriteId = Play::GetSpriteId("ship");
}

Ship::~Ship()
{
}

void Ship::Simulate(float timeStep)
{
    // --- Rotation: left / right arrow keys update the heading --------------
    const float turnSpeed = 3.0f;  // radians per second
    // PlayBuffer uses a Cartesian (y-up) world, so a POSITIVE angle turns the
    // ship counter-clockwise (to the left). Left arrow = turn left.
    if (Play::KeyDown(Play::KEY_LEFT))
        m_rotation += turnSpeed * timeStep;
    if (Play::KeyDown(Play::KEY_RIGHT))
        m_rotation -= turnSpeed * timeStep;

    // --- Thrust: only while SPACE is held ----------------------------------
    // The brief's pseudo-code assumes a y-DOWN screen (x += sin, y -= cos).
    // THIS PlayBuffer build is y-UP (Cartesian): the ship's nose points along
    // (-sin, +cos), so we flip both signs to push the ship the way it faces.
    if (Play::KeyDown(Play::KEY_SPACE))
    {
        m_acceleration.x -= m_thrust * sin(m_rotation) * timeStep;
        m_acceleration.y += m_thrust * cos(m_rotation) * timeStep;
    }

    // --- Run the shared physics integration --------------------------------
    Rigidbody::Simulate(timeStep);
}

void Ship::Collide(Rigidbody* other)
{
    // Polymorphism in action: we only reset when the other body is actually
    // an Asteroid. dynamic_cast returns nullptr if 'other' is not an Asteroid.
    if (dynamic_cast<Asteroid*>(other) != nullptr)
    {
        Reset();
    }
}

void Ship::Draw()
{
    Play::DrawSpriteRotated(m_spriteId, m_position, 0, m_rotation, 1.0f);
}

void Ship::Reset()
{
    m_position     = { 640.0f, 360.0f };
    m_velocity     = { 0.0f, 0.0f };
    m_acceleration = { 0.0f, 0.0f };
    m_rotation     = 0.0f;
}
