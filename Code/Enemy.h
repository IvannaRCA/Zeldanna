#pragma once
#include "BaseElement.h"
class Enemy :
    public BaseElement
{
    int _Rand;
    bool exit;
    int _Life;
    bool _IsDead;

public:
    Enemy();
    ~Enemy();

    void init();
    void update();
    void render(int rPosX, int rPosY);

    void setLife(int life) { _Life = life; };
    int getLife() { return _Life; };

    bool isDead() { return _IsDead; };
};

