
#include "Tile.h"

Tile::Tile()
    :m_num(0)
{
    spriteData.width = tileNS::width;
    spriteData.height = tileNS::height;
    spriteData.x = 0;
    spriteData.y = 0;
    spriteData.rect.left = 0;
    spriteData.rect.top = 0;
    spriteData.rect.right = tileNS::width;
    spriteData.rect.bottom = tileNS::height;

}

bool Tile::initialize(Game *gamePtr, int width, int height, int ncols,
    TextureManager *textureM)
{
    bool flag = Entity::initialize(gamePtr, width, height, ncols, textureM);
    spriteData.width = tileNS::width;
    spriteData.height = tileNS::height;
    spriteData.x = 0;
    spriteData.y = 0;
    spriteData.rect.left = 0;
    spriteData.rect.top = 0;
    spriteData.rect.right = tileNS::width;
    spriteData.rect.bottom = tileNS::height;
    colorFilter = graphicsNS::MAGENTA;
    return flag;
}

void Tile::update(float frameTime)
{
    Entity::update(frameTime);
}

void Tile::setNum(int num)
{
    // 引数チェック
    if (num != 1 || num != 2)
    {
        // 1か2でないのならば3で割り切れるはず
        // 1+2 -> 3, 3+3->6, 6+6->12, ...
        if (num % 3 != 0)
        {
            _ASSERT(false); // セットしようとした数が仕様上おかしい
        }
    }
    if (num < 768)
    {
        //テクスチャがないので表示できない
    }

    m_num = num;
    
    // テクスチャ入れ替え
    if (num == 1)
    {
        spriteData.rect.left = 0;
        spriteData.rect.top = 0;
    }
    else if (num == 2)
    {
        spriteData.rect.left = tileNS::width;
        spriteData.rect.top = 0;
    }
    else if (num % 3 == 0)
    {
        int addTime = 0;
        while (num != 3)
        {
            num /= 2;
            addTime += 1;
        }
        spriteData.rect.left = ((addTime + 2) % 4) * tileNS::width;
        spriteData.rect.top = ((addTime + 2) / 4) * tileNS::height; 
    }

    spriteData.rect.right = spriteData.rect.left + tileNS::width;
    spriteData.rect.bottom = spriteData.rect.top + tileNS::height;


}