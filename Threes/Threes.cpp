// Threes Clone App
// @author Okumura Hiroaki

#include "Threes.h"

//=============================================================================
// Constructor
//=============================================================================
Threes::Threes()
{}

//=============================================================================
// Destructor
//=============================================================================
Threes::~Threes()
{
    releaseAll();           // call onLostDevice() for every graphics item
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void Threes::initialize(HWND hwnd)
{
    Game::initialize(hwnd); // throws GameError

    // nebula texture
    if (!bgTexture.initialize(graphics, BACKGROUND_IMAGE))
    {
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background texture"));
    }
    if (!tilesTexture.initialize(graphics, TILES_IMAGE))
    {
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing tiles texture"));
    }

    if (!bg.initialize(graphics, 0, 0, 0, &bgTexture))
    {
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background"));
    }

    if (!tile.initialize(this, 0, 0, 3, &tilesTexture))
    {
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing tile"));
    }
    return;
}

//=============================================================================
// Update all game items
//=============================================================================
void Threes::update()
{
    tile.update(frameTime);
    tile.setNum(3);
}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void Threes::ai()
{}

//=============================================================================
// Handle collisions
//=============================================================================
void Threes::collisions()
{}

//=============================================================================
// Render game items
//=============================================================================
void Threes::render()
{
    graphics->spriteBegin();                // begin drawing sprites

    bg.draw();                          // add the orion nebula to the scene
    tile.draw();

    graphics->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void Threes::releaseAll()
{
    bgTexture.onLostDevice();
    tilesTexture.onLostDevice();

    Game::releaseAll();
    return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void Threes::resetAll()
{
    bgTexture.onResetDevice();
    tilesTexture.onResetDevice();

    Game::resetAll();
    return;
}
