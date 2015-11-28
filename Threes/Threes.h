// Threes Clone App
// @author Okumura Hiroaki


#ifndef _THREES_H             // Prevent multiple definitions if this 
#define _THREES_H             // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "textureManager.h"
#include "image.h"
#include "Field.h"

//=============================================================================
// This class is the core of the game
//=============================================================================
class Threes : public Game
{
private:
    // game items
    TextureManager bgTexture;      // background texture
    Image   bg;                    // background image
    Field   field;
    
    bool    m_isDragged;

public:
    // Constructor
    Threes();

    // Destructor
    virtual ~Threes();

    // Initialize the game
    void initialize(HWND hwnd);
    void update();      // must override pure virtual from Game
    void ai();          // "
    void collisions();  // "
    void render();      // "
    void releaseAll();
    void resetAll();
};

#endif