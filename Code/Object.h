#pragma once
#include "BaseElement.h"


class Object :
    public BaseElement
{
    bool _Hitten;
public:
    Object();
    ~Object();

    void init();
    void render();

    void setHitten(bool b) { _Hitten = b; };
    bool getHitten() { return _Hitten; };
};

