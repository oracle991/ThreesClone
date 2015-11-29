// Threes Clone App
// @author Okumura Hiroaki

#include "Threes.h"

//=============================================================================
// Constructor
//=============================================================================
Threes::Threes()
    : m_isDragged(false)
    , m_isGameOver(false)
{
}

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

    if (!bgTexture.initialize(graphics, BACKGROUND_IMAGE))
    {
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background texture"));
    }
    if (!bg.initialize(graphics, 0, 0, 0, &bgTexture))
    {
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background"));
    }

    if (!gameOverTexture.initialize(graphics, GAMEOVER_IMAGE))
    {
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing gameover texture"));
    }
    if (!gameOver.initialize(graphics, 0, 0, 0, &gameOverTexture))
    {
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background"));
    }
    gameOver.setVisible(false);
    gameOver.setX(GAME_WIDTH / 2 - 128);
    gameOver.setY(GAME_HEIGHT / 2 - 64);

    field.initialize(graphics, this);
    field.setPosition(GAME_WIDTH / 2 - tileNS::width * (fieldNS::width / 2), GAME_HEIGHT / 2 - tileNS::height * (fieldNS::height / 2));
    field.randomStart();
    return;
}

//=============================================================================
// Update all game items
//=============================================================================
void Threes::update()
{
    if (m_isGameOver)
    {
        if (input->getMouseLButton())
        {
            //クリックでリセット
            field.randomStart();
            m_isGameOver = false;
            gameOver.setVisible(false);
        }
    }
    if (m_isDragged && !input->getMouseDrag())
    {
        //ドラッグが終わった
        int startX, startY, endX, endY;
        startX = input->getMouseDragStartX();
        startY = input->getMouseDragStartY();
        endX = input->getMouseDragEndX();
        endY = input->getMouseDragEndY();

        if (std::abs(startX - endX) + std::abs(startY - endY) < 5)
        {
            //少な過ぎたら無視
            return;
        }

        if (std::abs(startX - endX) > std::abs(startY - endY))
        {
            int diffX = (startX - endX) > 0 ? -1 : 1;
            if (field.canMove(diffX, 0))
            {
                field.move(diffX, 0);
            }
            
        }
        else
        {
            int diffY = (startY - endY) > 0 ? -1 : 1;
            if (field.canMove(0, diffY))
            { 
                field.move(0, diffY);
            }
            
        }
        if (field.isGameOver())
        {
            m_isGameOver = true;
            gameOver.setVisible(true);
        }

    }
    m_isDragged = input->getMouseDrag();

    field.update(frameTime);
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
    field.render();
    gameOver.draw();

    graphics->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void Threes::releaseAll()
{
    bgTexture.onLostDevice();
    field.releaseAll();
    gameOverTexture.onLostDevice();
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
    field.resetAll();
    gameOverTexture.onResetDevice();
    Game::resetAll();
    return;
}
