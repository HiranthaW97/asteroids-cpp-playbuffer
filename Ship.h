#pragma once
#include "Rigidbody.h"

// ============================================================================
// Ship : public Rigidbody          <-- [INHERITANCE]
// ----------------------------------------------------------------------------
// The player's ship.
//
// [INHERITANCE]  "class Ship : public Rigidbody" means a Ship IS-A Rigidbody.
//                Ship automatically GETS (inherits) all of the base class's
//                data and behaviour without rewriting any of it:
//                   - data:      m_position, m_velocity, m_acceleration,
//                                m_rotation, m_radius   (declared in Rigidbody)
//                   - behaviour: Rigidbody::Simulate() physics + screen wrap,
//                                IsCollidingWith()      (the circle overlap test)
//                Ship then ADDS what only a ship needs: a thrust value and a
//                sprite id (see the private section below).
//
// [ABSTRACTION]  Rigidbody is an ABSTRACT class (it has "virtual void Draw()=0").
//                That pure virtual is a CONTRACT: any concrete body must supply
//                its own Draw(). Ship honours the contract by declaring Draw()
//                below, which is what makes Ship a class we are allowed to
//                instantiate ("new Ship()").
//
// [POLYMORPHISM] Simulate(), Collide() and Draw() are marked 'override'. Because
//                they are virtual in the base, a Rigidbody* that really points
//                at a Ship will run THESE versions (chosen at run time). That is
//                how the game loop can treat every object as a plain Rigidbody*
//                yet still get ship-specific behaviour.
// ============================================================================
class Ship : public Rigidbody
{
public:
    Ship();
    ~Ship() override;   // 'override' of the base virtual destructor

    // [POLYMORPHISM] Override the base physics: read the keyboard (thrust +
    // rotate), THEN call the inherited Rigidbody::Simulate() to move.
    void Simulate(float timeStep) override;

    // [POLYMORPHISM] Override collision response: if 'other' is an Asteroid,
    // reset the ship. (The base Rigidbody::Collide does nothing by default.)
    void Collide(Rigidbody* other) override;

    // [ABSTRACTION] Required implementation of the base's pure virtual Draw().
    void Draw() override;

private:
    void Reset();   // put the ship back to the centre, stationary

    // ---- Members that belong ONLY to Ship (not in the base class) ----------
    float m_thrust   = 500.0f;  // acceleration applied while thrusting
    int   m_spriteId = 0;       // id returned by Play::GetSpriteId("ship")
};
