#ifndef LEVEL_H
#define LEVEL_H

#define BLOCKCOUNTX 9   //Кол-во блоков по оси X
#define BLOCKCOUNTY 5   //Кол-во блоков по оси Y
#define BLOCKINITX 25   //Начальная позиция блока по оси X
#define BLOCKINITY 100  //Начальная позиция блока по оси Y
#define LEVELSCOUNT 3   //Кол-во уровней

enum blocks { empty, green, blue, red };

//Класс Уровень
class Level
{
public:
    explicit Level(int _number);
    ~Level();

    int number;         //Порядковый номер уровня
    int platformWidth;  //Ширина платформы
    int speed;          //Скорость полета шара
    unsigned char map[BLOCKCOUNTY][BLOCKCOUNTX];    //Карта блоков уровня

private:
    void fillMap(unsigned char _map[BLOCKCOUNTY][BLOCKCOUNTX]);
};

#endif // LEVEL_H
