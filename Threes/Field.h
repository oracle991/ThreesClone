// Threes Clone App
// Field.h
// �^�C�������i�[����N���X�B
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

    //�O���[�o�����W(2d)����^�C���C���f�b�N�X(����(0,0) ~ �E��(3,3))�ɕϊ�
    static void convertGlobalPosToFieldPos(int globalX, int globalY, int& fieldX, int& fieldY);

    void initialize(Graphics* graphics, Game* gamePtr);
    void update(float frameTime);
    void render();  //spriteBegin���Ă񂾌�ɌĂԂ���
    void releaseAll();
    void resetAll();

    void setPosition(int x, int y);
    void randomStart();
    void move(int diffX, int diffY);
};