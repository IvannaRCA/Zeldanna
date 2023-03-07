#include "HUD.h"

HUD::HUD()
{
	_Player = nullptr;
}

HUD::~HUD()
{
}

void HUD::init()
{
	// init
	_Hearts.init();
	_CoinImage.init();
	_CoinCounter.init();
	_LifeImage.init();
	_SwordSlot.init();
	_TFImage1.init();
	_TFImage2.init();
	_TFImage3.init();

	// Load images
	_Hearts.loadGraphic	("ZELDA/Sprites/HUD/hearts.png");
	_Hearts.setGraphicID();
	_Hearts.setWH(4, 16);
	_Hearts.setXY(0, 0);
	_Hearts.setWorldXY(0, 0);
	_Hearts.setScreenXY(176, 31);
	
	_LifeImage.loadGraphic("ZELDA/Sprites/HUD/lifeImage.png");
	_LifeImage.setGraphicID();
	_LifeImage.setWH(64, 16);
	_LifeImage.setXY(0, 0);
	_LifeImage.setWorldXY(0, 0);
	_LifeImage.setScreenXY(176, 16);
	
	_CoinImage.loadGraphic("ZELDA/Sprites/HUD/coinImage.png");
	_CoinImage.setGraphicID();
	_CoinImage.setWH(16, 16);
	_CoinImage.setXY(0, 0);
	_CoinImage.setWorldXY(0, 0);
	_CoinImage.setScreenXY(64, 24);

	_CoinCounter.loadGraphic("ZELDA/Sprites/HUD/numbers.png");
	_CoinCounter.setGraphicID();
	_CoinCounter.setWH(16, 16);
	_CoinCounter.setXY(0, 0);
	_CoinCounter.setWorldXY(0, 0);
	_CoinCounter.setScreenXY(80, 24);

	_SwordSlot.loadGraphic("ZELDA/Sprites/HUD/swordSlot.png");
	_SwordSlot.setGraphicID();
	_SwordSlot.setWH(16, 25);
	_SwordSlot.setXY(0, 0);
	_SwordSlot.setWorldXY(0, 0);
	_SwordSlot.setScreenXY(120, 16);

	_TFImage1.loadGraphic("ZELDA/Sprites/HUD/triforce.png");
	_TFImage1.setGraphicID();
	_TFImage1.setWH(16, 16);
	_TFImage1.setXY(0, 0);
	_TFImage1.setWorldXY(0, 0);
	_TFImage1.setScreenXY(16, 31);

	_TFImage2.loadGraphic("ZELDA/Sprites/HUD/triforce.png");
	_TFImage2.setGraphicID();
	_TFImage2.setWH(16, 16);
	_TFImage2.setXY(0, 0);
	_TFImage2.setWorldXY(0, 0);
	_TFImage2.setScreenXY(26, 31);

	_TFImage3.loadGraphic("ZELDA/Sprites/HUD/triforce.png");
	_TFImage3.setGraphicID();
	_TFImage3.setWH(16, 16);
	_TFImage3.setXY(0, 0);
	_TFImage3.setWorldXY(0, 0);
	_TFImage3.setScreenXY(21, 22);
}

void HUD::update()
{
}

void HUD::render()
{
	_Hearts.render(_Player->getLife());
	_LifeImage.render();
	_CoinImage.render();
	_CoinCounter.renderNumberAnim(_Player->getRupees(), 0);
	if (_Player->getSword())
	{
		_SwordSlot.render();
	}
	if (_Player->getTriforcePieces() == 1)
	{
		_TFImage1.render();
	}
	if (_Player->getTriforcePieces() == 2)
	{
		_TFImage1.render();
		_TFImage2.render();
	}
	if (_Player->getTriforcePieces() == 3)
	{
		_TFImage1.render();
		_TFImage2.render();
		_TFImage3.render();
	}
}
