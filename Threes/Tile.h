// Threes Clone App
// Tile
// @author Okumura Hiroaki

#ifndef _TILE_H
#define _TILE_H
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace tileNS
{
    const int width = 64;
    const int height = 64;
    const int TEXTURE_COLS = 4;
}

class Tile : public Entity
{
public:
    Tile();
    bool initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM) override;
    void update(float frameTime);
    void setNum(int num);
    int getNum() const { return m_num; };
private:
    int m_num;
};
#endif