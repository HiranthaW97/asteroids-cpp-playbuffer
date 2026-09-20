#pragma once
#include "Play.h"

// ============================================================================
// Rigidbody  (ABSTRACT BASE CLASS)
// ----------------------------------------------------------------------------
// Every physical object in the game (Ship, Asteroid, ...) IS-A Rigidbody.
// This class holds the shared physics state and defines the interface that
// every subclass must implement. It is abstract because Draw() is a
// PURE VIRTUAL function (= 0), so you can never create a plain Rigidbody.
//
// C# analogy: this is like an `abstract class Rigidbody` with an
// `abstract void Draw();`.
// ============================================================================
class Rigidbody
{
public:
    // Construct with a starting position and radius (used for collisions).
    Rigidbody(Play::Point2D position, float radius);

    // A base class with virtual methods MUST have a virtual destructor,
    // otherwise deleting through a Rigidbody* leaks the subclass part.
    virtual ~Rigidbody();

    // --- Virtual: subclasses may override, but there is a default ----------
    // Advance the physics by one time step (see pseudo-code in the brief).
    virtual void Simulate(float timeStep);

    // Resolve a collision against another rigid body. Polymorphism means the
    // 'other' can be any subclass. Default does nothing; Ship overrides it.
    virtual void Collide(Rigidbody* other);

    // --- Pure virtual: EVERY subclass MUST implement this ------------------
    virtual void Draw() = 0;   // <- this "= 0" is what makes the class abstract

    // --- Simple helpers shared by all bodies -------------------------------
    Play::Point2D GetPosition() const { return m_position; }
    float         GetRadius()   const { return m_radius; }

    // Returns true if this body overlaps 'other' (circle vs circle).
    bool IsCollidingWith(const Rigidbody* other) const;

protected:
    // Physics state shared by all rigid bodies (protected = visible to subclasses).
    Play::Point2D  m_position     { 0.0f, 0.0f };
    Play::Vector2D m_velocity     { 0.0f, 0.0f };
    Play::Vector2D m_acceleration { 0.0f, 0.0f };
    float          m_rotation     = 0.0f;   // in RADIANS
    float          m_radius       = 0.0f;   // for collision detection
};
