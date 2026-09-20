#include "Play.h"
#include "Rigidbody.h"
#include "Ship.h"
#include "Asteroid.h"

// ============================================================================
// MainGame.cpp
// ----------------------------------------------------------------------------
// The brief allows ONLY THREE functions in this file:
//     MainGameEntry, MainGameUpdate, MainGameExit
// Do not add any other functions here. All game logic lives in the classes.
// ============================================================================

// Window settings.
constexpr int DISPLAY_WIDTH  = 1280;
constexpr int DISPLAY_HEIGHT = 720;
constexpr int DISPLAY_SCALE  = 1;

// Number of rigid bodies: 1 ship + N asteroids.
constexpr int NUM_ASTEROIDS = 5;
constexpr int NUM_BODIES     = NUM_ASTEROIDS + 1;

// An array of BASE-CLASS pointers. This is what makes polymorphism work:
// we loop over Rigidbody* and each call resolves to the right subclass.
Rigidbody** g_rigidbody = nullptr;

// ---------------------------------------------------------------------------
void MainGameEntry(PLAY_IGNORE_COMMAND_LINE)
{
    Play::CreateManager(DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE);
    // Load every .png in data/sprites/ so we can look them up by name later
    // (e.g. Play::GetSpriteId("ship")). CentreAllSpriteOrigins() makes each
    // sprite rotate/draw about its middle, which is what DrawSpriteRotated wants.
    Play::CentreAllSpriteOrigins();

    // Dynamically allocate the array of rigid bodies.
    g_rigidbody = new Rigidbody*[NUM_BODIES];

    // Index 0 is the player's ship...
    g_rigidbody[0] = new Ship();

    // ...the rest are asteroids.
    for (int i = 1; i < NUM_BODIES; i++)
        g_rigidbody[i] = new Asteroid();
}

// ---------------------------------------------------------------------------
bool MainGameUpdate(float elapsedTime)
{
    Play::ClearDrawingBuffer(Play::cBlack);

    // Collision pass: test every pair once, using ONLY Rigidbody* (polymorphism).
    for (int i = 0; i < NUM_BODIES; i++)
        for (int j = i + 1; j < NUM_BODIES; j++)
            if (g_rigidbody[i]->IsCollidingWith(g_rigidbody[j]))
            {
                g_rigidbody[i]->Collide(g_rigidbody[j]);
                g_rigidbody[j]->Collide(g_rigidbody[i]);
            }

    // Simulate + draw pass: dynamic dispatch picks the right override for each.
    for (int i = 0; i < NUM_BODIES; i++)
    {
        g_rigidbody[i]->Simulate(elapsedTime);
        g_rigidbody[i]->Draw();
    }

    Play::PresentDrawingBuffer();
    return Play::KeyDown(Play::KEY_ESCAPE);  // ESC quits
}

// ---------------------------------------------------------------------------
int MainGameExit(void)
{
    // Free every body, then the array itself. (No garbage collector in C++!)
    if (g_rigidbody != nullptr)
    {
        for (int i = 0; i < NUM_BODIES; i++)
            delete g_rigidbody[i];
        delete[] g_rigidbody;
        g_rigidbody = nullptr;
    }

    Play::DestroyManager();
    return PLAY_OK;
}
