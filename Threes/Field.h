// Threes Clone App
// Field.h
// タイル情報を格納するクラス。
// @author Okumura Hiroaki

#include "TextureManager.h"
#include "Tile.h"
#include "Array2d.h"

class Game;
class Graphics;
namespace fieldNS
{
    const int width = 4;
    const int height = 4;
}

class Field
{
private:
    TextureManager m_tilesTexture;
    Array2d<Tile>  m_tiles;
    int m_x, m_y;

public:
    Field();
    ~Field();

    //グローバル座標(2d)からタイルインデックス(左上(0,0) ~ 右下(3,3))に変換
    static void convertGlobalPosToFieldPos(int globalX, int globalY, int& fieldX, int& fieldY);

    void initialize(Graphics* graphics, Game* gamePtr);
    void update(float frameTime);
    void render();  //spriteBeginを呼んだ後に呼ぶこと
    void releaseAll();
    void resetAll();

    void setPosition(int x, int y);
    void randomStart();
    void move(int diffX, int diffY);
};