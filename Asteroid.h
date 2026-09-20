#pragma once
#include "Rigidbody.h"

// ============================================================================
// Asteroid : public Rigidbody      <-- [INHERITANCE]
// ----------------------------------------------------------------------------
// A drifting, spinning rock.
//
// [INHERITANCE]  Like Ship, an Asteroid IS-A Rigidbody, so it inherits the same
//                physics state (position/velocity/acceleration/rotation/radius)
//                and the shared Rigidbody::Simulate() movement + screen wrap.
//                It ADDS three members only an asteroid needs: a visual scale,
//                a spin speed, and a sprite id.
//
// [ABSTRACTION]  Rigidbody's pure virtual Draw() forces every body to say how it
//                draws itself. Asteroid satisfies that contract with its own
//                Draw() below (drawing the asteroid sprite at its scale).
//
// [POLYMORPHISM] Simulate() and Draw() override the base versions, so when the
//                game loop calls them through a Rigidbody* that points at an
//                Asteroid, these asteroid versions run (dynamic dispatch).
//
// Note: Asteroid does NOT override Collide(). It simply INHERITS the base
// Rigidbody::Collide() (which does nothing) - an asteroid ignores being hit.
// ============================================================================
class Asteroid : public Rigidbody
{
public:
    Asteroid();          // randomizes velocity, scale and spin (see .cpp)
    ~Asteroid() override;

    // [POLYMORPHISM] Override: run the inherited physics AND spin the rock.
    void Simulate(float timeStep) override;

    // [ABSTRACTION] Required implementation of the base's pure virtual Draw().
    void Draw() override;

private:
    // ---- Members that belong ONLY to Asteroid (not in the base class) ------
    float m_scale         = 1.0f;   // visual size, randomized within reason
    float m_rotationSpeed = 0.0f;   // radians per second, randomized
    int   m_spriteId      = 0;      // id from Play::GetSpriteId("asteroid")
};
