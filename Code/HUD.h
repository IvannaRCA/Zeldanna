#pragma once
#include "BaseElement.h"
#include "Player.h"
class HUD
{
	Player* _Player;
	BaseElement _Hearts;
	BaseElement _CoinImage;
	BaseElement _CoinCounter;
	BaseElement _LifeImage;
	BaseElement _SwordSlot;
	BaseElement _TFImage1;
	BaseElement _TFImage2;
	BaseElement _TFImage3;
public:
	HUD();
	~HUD();

	void init();
	void update();
	void render();

	void setPlayerPointer(Player* p) { _Player = p; };
};

