#include "Ship.h"
#include "Asteroid.h"   // needed for the dynamic_cast in Collide()

// [INHERITANCE] The constructor forwards to the BASE class constructor via the
// initialiser list ": Rigidbody(...)". This is how the inherited members
// m_position and m_radius get set up before the Ship-specific code runs.
Ship::Ship()
    : Rigidbody(Play::Point2D{ 640.0f, 360.0f }, 30.0f)  // centre of a 1280x720 window
{
    // [PlayBuffer API] GetSpriteId() looks up a sprite that was auto-loaded
    // from data/sprites/ship.png and returns the integer id we draw with later.
    m_spriteId = Play::GetSpriteId("ship");
}

Ship::~Ship()
{
}

// [POLYMORPHISM] This overrides Rigidbody::Simulate(). When the game loop calls
// Simulate() through a Rigidbody*, THIS version runs for a ship.
void Ship::Simulate(float timeStep)
{
    // --- Rotation: left / right arrow keys update the heading --------------
    const float turnSpeed = 3.0f;  // radians per second
    
    // [PlayBuffer API] KeyDown() is TRUE for as long as the key is held.
    // PlayBuffer uses a Cartesian (y-up) world, so a POSITIVE angle turns the
    // ship counter-clockwise (to the left). Left arrow = turn left.
    if (Play::KeyDown(Play::KEY_LEFT))
        m_rotation += turnSpeed * timeStep;
    if (Play::KeyDown(Play::KEY_RIGHT))
        m_rotation -= turnSpeed * timeStep;

    // --- Thrust: only while SPACE is held ----------------------------------
    // We write into the INHERITED member m_acceleration (defined in Rigidbody).
    // The brief's pseudo-code assumes a y-DOWN screen (x += sin, y -= cos).
    // THIS PlayBuffer build is y-UP (Cartesian): the ship's nose points along
    // (-sin, +cos), so we flip both signs to push the ship the way it faces.
    if (Play::KeyDown(Play::KEY_SPACE))
    {
        m_acceleration.x -= m_thrust * sin(m_rotation) * timeStep;
        m_acceleration.y += m_thrust * cos(m_rotation) * timeStep;
    }

    // [INHERITANCE] Reuse the shared physics (position/velocity integration and
    // screen wrapping) instead of copying it here. "Rigidbody::" calls the
    // BASE version explicitly.
    Rigidbody::Simulate(timeStep);
}

// [POLYMORPHISM] The required "collision demonstrates polymorphism" part.
void Ship::Collide(Rigidbody* other)
{
    // 'other' is a base Rigidbody*, but we only care if it is REALLY an Asteroid.
    // dynamic_cast inspects the true run-time type: it returns a valid pointer
    // if 'other' is an Asteroid, or nullptr if it is anything else. This is
    // polymorphism used to make a type-specific decision safely.
    if (dynamic_cast<Asteroid*>(other) != nullptr)
    {
        Reset();
    }
}

// [ABSTRACTION] Concrete implementation of the base's pure virtual Draw().
void Ship::Draw()
{
    // [PlayBuffer API] DrawSpriteRotated(id, position, frame, angle, scale).
    // We pass the inherited m_position and m_rotation so the sprite is drawn
    // where the physics has moved us and facing our current heading.
    Play::DrawSpriteRotated(m_spriteId, m_position, 0, m_rotation, 1.0f);
}

void Ship::Reset()
{
    // These are all INHERITED members from Rigidbody.
    m_position     = { 640.0f, 360.0f };
    m_velocity     = { 0.0f, 0.0f };
    m_acceleration = { 0.0f, 0.0f };
    m_rotation     = 0.0f;
}
