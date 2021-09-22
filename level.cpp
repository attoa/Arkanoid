#include "level.h"

unsigned char map1[BLOCKCOUNTY][BLOCKCOUNTX]
{
    {red, empty, red, empty, red, empty, red, empty, red},
    {empty, empty, empty, empty, empty, empty, empty, empty, empty},
    {red, empty, red, empty, red, empty, red, empty, red},
    {empty, empty, empty, empty, empty, empty, empty, empty, empty},
    {red, empty, red, empty, red, empty, red, empty, red}
};

unsigned char map2[BLOCKCOUNTY][BLOCKCOUNTX]
{
    {red, green, red, green, red, green, red, green, red},
    {empty, empty, empty, empty, empty, empty, empty, empty, empty},
    {red, green, red, green, red, green, red, green, red},
    {empty, empty, empty, empty, empty, empty, empty, empty, empty},
    {red, green, red, green, red, green, red, green, red}
};

unsigned char map3[BLOCKCOUNTY][BLOCKCOUNTX]
{
    {red, green, red, green, red, green, red, green, red},
    {empty, blue, empty, blue, empty, blue, empty, blue, empty},
    {red, green, red, green, red, green, red, green, red},
    {empty, blue, empty, blue, empty, blue, empty, blue, empty},
    {red, green, red, green, red, green, red, green, red}
};

Level::Level(int _number)
{
    switch (_number) {
    case 1:
        number = 1;
        platformWidth = 100;
        speed = 10;
        fillMap(map1);
        break;

    case 2:
        number = 2;
        platformWidth = 90;
        speed = 9;
        fillMap(map2);
        break;

    case 3:
        number = 3;
        platformWidth = 80;
        speed = 8;
        fillMap(map3);
        break;
    }
}

Level::~Level() {}

void Level::fillMap(unsigned char _map[BLOCKCOUNTY][BLOCKCOUNTX])
{
    for (int i = 0; i < BLOCKCOUNTY; ++i)
        for (int j = 0; j < BLOCKCOUNTX; ++j)
            map[i][j] = _map[i][j];
}
