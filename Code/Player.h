#pragma once
#include "BaseElement.h"

class Player :
    public BaseElement
{
    int _MaxLife;
    int _Life;
    int _Rupee;
    int _TriforcePieces;
    bool _Sword;
    bool _Attack;
public:
    Player();
    ~Player();

    void init();
    void update();
    void render(int posX, int posY);

    void setMaxLife(int num) { _MaxLife = num; };
    int getMaxLife() { return _MaxLife; };

    void setLife(int num) { _Life = num; };
    int getLife() { return _Life; };
    
    void setRupees(int num) { _Rupee = num; };
    int getRupees() { return _Rupee; };

    void setTriforcePieces(int num) { _TriforcePieces = num; };
    int getTriforcePieces() { return _TriforcePieces; };
    
    void setSword(bool value) { _Sword = value; };
    bool getSword() { return _Sword; };

    void setAttack(bool value) { _Attack = value; };
    bool getAttack() { return _Attack; };
};

