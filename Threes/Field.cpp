// Threes Clone App
// @author Okumura Hiroaki

#include "Field.h"
#include "game.h"
#include <random>
#include <vector>
#include <algorithm>

//=============================================================================
// Constructor
//=============================================================================
Field::Field()
    : m_x(0)
    , m_y(0)
{
}

//=============================================================================
// Destructor
//=============================================================================
Field::~Field()
{
    releaseAll();           // call onLostDevice() for every graphics item
}


static void convertGlobalPosToFieldPos(int windowX, int windowY, int& fieldX, int& fieldY)
{
    int centerX = GAME_WIDTH / 2;
    int centerY = GAME_HEIGHT / 2;

    fieldX = (windowX - centerX / tileNS::width) + fieldNS::width / 2;
    fieldY = (windowY - centerY / tileNS::height) + fieldNS::height / 2;

}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void Field::initialize(Graphics* graphics, Game* gamePtr)
{
    if (!m_tilesTexture.initialize(graphics, TILES_IMAGE))
    {
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing tiles texture"));
    }

    m_tiles.setSize(fieldNS::width, fieldNS::height);

    for (int y = 0; y < fieldNS::height; y++)
    {
        for (int x = 0; x < fieldNS::width; x++)
        {
            if (!m_tiles(x,y).initialize(gamePtr, 0, 0, 3, &m_tilesTexture))
            {
                throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing tile"));
            }
        }
    }

    
}


//=============================================================================
// Update all game items
//=============================================================================
void Field::update(float frameTime)
{

    for (int y = 0; y < fieldNS::height; y++)
    {
        for (int x = 0; x < fieldNS::width; x++)
        {
            m_tiles(x, y).update(frameTime);
        }
    }
}


//=============================================================================
// Render game items
//=============================================================================
void Field::render()
{
    for (int y = 0; y < fieldNS::height; y++)
    {
        for (int x = 0; x < fieldNS::width; x++)
        {
            m_tiles(x, y).draw();
        }
    }
}


//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void Field::releaseAll()
{
    m_tilesTexture.onLostDevice();
}


//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void Field::resetAll()
{
    m_tilesTexture.onResetDevice();
}


void Field::setPosition(int x, int y)
{
    m_x = x;
    m_y = y;

    // u : tmp_y, t : tmp_x
    for (int u = 0; u < fieldNS::height; u++)
    {
        for (int t = 0; t < fieldNS::width; t++)
        {
            m_tiles(t, u).setX(m_x + t * tileNS::width);
            m_tiles(t, u).setY(m_y + u * tileNS::height);
        }
    }
}

void Field::randomStart()
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, 3);

    //[1]は0~3個。[2]は0~3個。[3]は0~3個。
    //タイル数が2個以下だった場合強制的に3個にする(各1個)
    int tile_num_1 = dist(mt);
    int tile_num_2 = dist(mt);
    int tile_num_3 = dist(mt);

    if (tile_num_1 + tile_num_2 + tile_num_3 < 3)
    {
        tile_num_1 = 1;
        tile_num_2 = 1;
        tile_num_3 = 1;
    }

    //tile_numを元にランダムで座標を決めていく
    std::vector<std::pair<int, int>> points;
    for (int u = 0; u < fieldNS::height; u++)
    {
        for (int t = 0; t < fieldNS::width; t++)
        {
            points.push_back(std::pair<int, int>(t, u));
        }
    }
    std::shuffle(points.begin(), points.end(), mt);

    int acc_count = 0;
    for (int i = 0; i < tile_num_1; i++)
    {
        int x = points[i + acc_count].first;
        int y = points[i + acc_count].second;
        m_tiles(x, y).setNum(1);
    }
    acc_count += tile_num_1;

    for (int i = 0; i < tile_num_2; i++)
    {
        int x = points[i + acc_count].first;
        int y = points[i + acc_count].second;
        m_tiles(x, y).setNum(2);
    }
    acc_count += tile_num_2;

    for (int i = 0; i < tile_num_3; i++)
    {
        int x = points[i + acc_count].first;
        int y = points[i + acc_count].second;
        m_tiles(x, y).setNum(3);
    }
    acc_count += tile_num_3;
}


void Field::move(int diffX, int diffY)
{
    if (diffX == 1)
    {
        //この辺、左右と上下をまとめられそうな気がするが、読みやすさのためあえてまとめない。

        //右方向に動く
        for (int x = fieldNS::width - 2; x >= 0; x--)
        {
            for (int y = 0; y < fieldNS::height; y++)
            {
                int rightNum = m_tiles(x + 1, y).getNum();
                //右にものがなければ動く。
                if (rightNum == 0)
                {
                    m_tiles(x + 1, y).setNum(m_tiles(x,y).getNum());
                    m_tiles(x, y).setNum(0);
                }
            }
        }
    }
    else if (diffX == -1)
    {
        //左方向に動く
        for (int x = 1; x < fieldNS::width; x++)
        {
            for (int y = 0; y < fieldNS::height; y++)
            {
                int leftNum = m_tiles(x - 1, y).getNum();
                //左にものがなければ動く。
                if (leftNum == 0)
                {
                    m_tiles(x - 1, y).setNum(m_tiles(x, y).getNum());
                    m_tiles(x, y).setNum(0);
                }
            }
        }
    }
    else if (diffY == 1)
    {
        //下方向に動く
        for (int y = fieldNS::height - 2; y >= 0; y--)
        {
            for (int x = 0; x < fieldNS::width; x++)
            {
                int downNum = m_tiles(x, y + 1).getNum();
                //下にものがなければ動く。
                if (downNum == 0)
                {
                    m_tiles(x, y + 1).setNum(m_tiles(x, y).getNum());
                    m_tiles(x, y).setNum(0);
                }
            }
        }
    }
    else if (diffY == -1)
    {
        //上方向に動く
        for (int y = 1; y < fieldNS::height; y++)
        {
            for (int x = 0; x < fieldNS::width; x++)
            {
                int upNum = m_tiles(x, y - 1).getNum();
                //上にものがなければ動く。
                if (upNum == 0)
                {
                    m_tiles(x, y - 1).setNum(m_tiles(x, y).getNum());
                    m_tiles(x, y).setNum(0);
                }
            }
        }
    }
}
