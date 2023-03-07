#include "SceneGame.h"
#include "SceneDirector.h"
#include "SoundManager.h"
#include "Map.h"

extern SceneDirector* scene_director;
extern SoundManager* sound;
extern Map* mapa;
extern Uint32 global_elapsed_time;

void SceneGame::reinit()
{
    // Player
    _Player.setLife(6);
    _Player.setMaxLife(6);
    _Player.setRupees(0);
    _Player.setWorldXY(55*16, 52*16);
    _Player.setSword(false);
    _Player.setTriforcePieces(0);

    // Objects
    _Sword.setHitten(false);
    initHearts(&_Heart);
    initRupees(&_Rupee);
    _TF1.setHitten(false);
    _TF2.setHitten(false);
    _TF3.setHitten(false);

    // Music
    sound->playSound(_Music1, "ZELDA/Sound/Music/Overworld.ogg", -1);
    sound->setSoundVolume(_Music1, 30);

    mReinit = false;
}
void SceneGame::init()
{
    _FrameTime = 0;    

    // Map
    mapa->init();
    mapa->setFileMap("ZELDA/Mapa.tmx");
    mapa->setTileset("ZELDA/overworldtiles.png");
    mapa->setMap();
    mapa->setPlayerObject(&_Player);
    
    // Player
    _Player.init();
    _Player.loadGraphic("ZELDA/Sprites/LinkAndObjects/link2.png"); // 64x32
    _Player.setGraphicID();
    _Player.setWH(38, 38);                // w-h de cada sprite
    _Player.setXY(0, 0);                  // x-y del sprite
    _Player.setWorldXY(55*16, 52*16);         // x-y del sprite en el mundo
    _DamageSound = sound->loadAndGetSoundID("ZELDA/Sound/FX/recieve-damage.ogg");
    _SwordSound = sound->loadAndGetSoundID("ZELDA/Sound/FX/attack.ogg");
    
    // HUD
    _HUD.init();
    _HUD.setPlayerPointer(&_Player);

    // Enemies
    initRedEnemy(&_RedEnemy);
    initBlueEnemy(&_BlueEnemy);

    // Sword
    _Sword.init();
    _Sword.loadGraphic("ZELDA/Sprites/LinkAndObjects/sword.png"); // 64x32
    _Sword.setGraphicID();
    _Sword.setWH(16, 16);                // w-h de cada sprite
    _Sword.setXY(0, 0);                  // x-y del sprite
    _Sword.setWorldXY(52*16, 48*16);

    // Rupees
    initRupees(&_Rupee);
    _CoinSound = sound->loadAndGetSoundID("ZELDA/Sound/FX/coin.ogg");

    // Hearts
    initHearts(&_Heart);

    // Triforce Pieces
        // 1
    _TF1.init();
    _TF1.loadGraphic("ZELDA/Sprites/LinkAndObjects/triforce.png");
    _TF1.setGraphicID();
    _TF1.setWH(16, 16);
    _TF1.setXY(0, 0);
    _TF1.setWorldXY(0, 0);
    _TF1.setWorldXY(8*16, 51*16);
        // 2
    _TF2.init();
    _TF2.loadGraphic("ZELDA/Sprites/LinkAndObjects/triforce.png");
    _TF2.setGraphicID();
    _TF2.setWH(16, 16);
    _TF2.setXY(0, 0);
    _TF2.setWorldXY(0, 0);
    _TF2.setWorldXY(55*16, 7*16);
        // 3
    _TF3.init();
    _TF3.loadGraphic("ZELDA/Sprites/LinkAndObjects/triforce.png");
    _TF3.setGraphicID();
    _TF3.setWH(16, 16);
    _TF3.setXY(0, 0);
    _TF3.setWorldXY(0, 0);
    _TF3.setWorldXY(135*16, 7*16);
    _TFSound = sound->loadAndGetSoundID("ZELDA/Sound/Music/Triforce.ogg");
}

void SceneGame::update()
{
    _FrameTime += global_elapsed_time;

    // Player update
    _Player.update();
    _Player.worldCollision();
    playerAttack(&_RedEnemy);
    playerAttack(&_BlueEnemy);

    // Enemies update
    updateEnemies(&_RedEnemy);
    updateEnemies(&_BlueEnemy);
    worldCollisionEnemies(&_RedEnemy);
    worldCollisionEnemies(&_BlueEnemy);
    enemyCollision(&_RedEnemy);
    enemyCollision(&_BlueEnemy);

    // Rupees collision with Player
    rupeeCollision(&_Rupee);
    worldCollisionRupees(&_Rupee);

    // Hearts collision with Player
    heartCollision(&_Heart);

    // Sword collision with Player
    if (_Player.isCollision(_Player.getRect(), _Sword.getRect()))
    {
        if (_FrameTime >= 50)
        {
            if (!_Sword.getHitten())
            {
                sound->playSound(_CoinSound, "ZELDA/Sound/FX/coin.ogg", 0);
                sound->setSoundVolume(_CoinSound, 30);
                _Sword.setHitten(true);
                _Player.setSword(true);
            }
            _FrameTime = 0;
        }
    }

    // Triforce Piece collision with Player
    triforceCollision(&_TF1);
    triforceCollision(&_TF2);
    triforceCollision(&_TF3);

    // Music
    if (sound->isPlaying(_TFSound))
    {
        sound->pauseSound(_Music1);
        if (_FrameTime >= 7500)
        {
            // Win
            if (_Player.getTriforcePieces() == 3)
            {
                sound->haltSound(_Music1);
                scene_director->changeScene(WIN);
            }
            sound->resumeSound(_Music1);
        }
    }

    // Death
    if (_Player.getLife() <= 0)
    {
        sound->haltSound(_Music1);
        scene_director->changeScene(GAMEOVER);
    }
}

void SceneGame::render()
{
    _HUD.render();
    mapa->render();
    renderRupees(&_Rupee);
    renderheart(&_Heart);
    _Sword.render();
    renderTriforce(&_TF1);
    renderTriforce(&_TF2);
    renderTriforce(&_TF3);
    renderEnemy(&_RedEnemy);
    renderEnemy(&_BlueEnemy);
    _Player.render(_Player.getSpriteX(), _Player.getSpriteY());
}

// PLAYER ATTACK
void SceneGame::playerAttack(vector<Enemy>* enemy)
{
    int _FrameRate = 200;
    for (unsigned int i = 0; i < enemy->size(); i++)
    {
        if (_Player.getAttack())
        {
            if (_FrameTime > _FrameRate)
            {
                switch (_Player.getDirection())
                {
                case UP:
                    if (enemy->at(i).getY() + 16 < _Player.getY() + 10 && enemy->at(i).getY() + 16 > _Player.getY() - 10 && enemy->at(i).getX() + 8 >= _Player.getX() + 14 && enemy->at(i).getX() + 8 <= _Player.getX() + 24)
                    {
                        sound->playSound(_SwordSound, "ZELDA/Sound/FX/attack.ogg", 0);
                        sound->setSoundVolume(_SwordSound, 30);
                        int life = enemy->at(i).getLife();
                        life--;
                        enemy->at(i).setLife(life);
                        if (enemy->at(i).isDead())
                        {
                            enemy->erase(enemy->begin() + i);
                            int rndC = rand() % 10;
                            if (rndC == 5)
                            {
                                sound->playSound(_CoinSound, "ZELDA/Sound/FX/coin.ogg", 0);
                                sound->setSoundVolume(_SwordSound, 30);
                                int coin = _Player.getRupees();
                                coin++;
                                _Player.setRupees(coin);
                            }
                        }
                        _FrameTime = 0;
                    }
                    break;
                case DOWN:
                    if (enemy->at(i).getY() > _Player.getY() + 28 && enemy->at(i).getY() < _Player.getY() + 38 && enemy->at(i).getX() + 8 > _Player.getX() + 14 && enemy->at(i).getX() + 8 < _Player.getX() + 24)
                    {
                        sound->playSound(_SwordSound, "ZELDA/Sound/FX/attack.ogg", 0);
                        sound->setSoundVolume(_SwordSound, 30);
                        int life = enemy->at(i).getLife();
                        life--;
                        enemy->at(i).setLife(life);
                        if (enemy->at(i).isDead())
                        {
                            enemy->erase(enemy->begin() + i);
                            int rndC = rand() % 10;
                            if (rndC == 5)
                            {
                                sound->playSound(_CoinSound, "ZELDA/Sound/FX/coin.ogg", 0);
                                sound->setSoundVolume(_SwordSound, 30);
                                int coin = _Player.getRupees();
                                coin++;
                                _Player.setRupees(coin);
                            }
                        }
                        _FrameTime = 0;
                    }
                    break;
                case RIGHT:
                    if (enemy->at(i).getX() > _Player.getX() + 28 && enemy->at(i).getX() < _Player.getX() + 38 && enemy->at(i).getY() + 8 >= _Player.getY() + 16 && enemy->at(i).getY() + 8 <= _Player.getY() + 22)
                    {
                        sound->playSound(_SwordSound, "ZELDA/Sound/FX/attack.ogg", 0);
                        sound->setSoundVolume(_SwordSound, 30);
                        int life = enemy->at(i).getLife();
                        life--;
                        enemy->at(i).setLife(life);
                        if (enemy->at(i).isDead())
                        {
                            enemy->erase(enemy->begin() + i);
                            int rndC = rand() % 10;
                            if (rndC == 5)
                            {
                                sound->playSound(_CoinSound, "ZELDA/Sound/FX/coin.ogg", 0);
                                sound->setSoundVolume(_SwordSound, 30);
                                int coin = _Player.getRupees();
                                coin++;
                                _Player.setRupees(coin);
                            }
                        }
                        _FrameTime = 0;
                    }
                    break;
                case LEFT:
                    if (enemy->at(i).getX() + 16 < _Player.getX() + 10 && enemy->at(i).getX() + 16 > _Player.getX() && enemy->at(i).getY() + 8 <= _Player.getY() + 24 && enemy->at(i).getY() + 8 >= _Player.getY() + 14)
                    {
                        sound->playSound(_SwordSound, "ZELDA/Sound/FX/attack.ogg", 0);
                        sound->setSoundVolume(_SwordSound, 30);
                        int life = enemy->at(i).getLife();
                        life--;
                        enemy->at(i).setLife(life);
                        if (enemy->at(i).isDead())
                        {
                            enemy->erase(enemy->begin() + i);
                            int rndC = rand() % 10;
                            if (rndC == 5)
                            {
                                sound->playSound(_CoinSound, "ZELDA/Sound/FX/coin.ogg", 0);
                                sound->setSoundVolume(_SwordSound, 30);
                                int coin = _Player.getRupees();
                                coin++;
                                _Player.setRupees(coin);
                            }
                        }
                        _FrameTime = 0;
                    }
                    break;
                default:
                    break;
                }
            }
        }
    }
}

// ENEMIES
void SceneGame::initRedEnemy(vector<Enemy>* enemy)
{
    enemy->resize(40 + (rand() % 10));
    for (unsigned int i = 0; i < enemy->size(); i++)
    {
        enemy->at(i).init();
        enemy->at(i).loadGraphic("ZELDA/Sprites/Enemies/red_enemy.png");
        enemy->at(i).setGraphicID();
        enemy->at(i).setWH(16, 16);                // w-h de cada sprite
        enemy->at(i).setXY(0, 0);                  // x-y del sprite
        enemy->at(i).setLife(1);
        
        int rndX = rand() % 2304;
        int rndY = rand() % 880;
        while (mapa->getTileID(rndX/16, rndY/16) != 3)
        {
            rndX = rand() % 2304;
            rndY = rand() % 880;
        }
        enemy->at(i).setWorldXY(rndX, rndY);
    }
}
void SceneGame::initBlueEnemy(vector<Enemy>* enemy)
{
    enemy->resize(20 + (rand() % 10));
    for (unsigned int i = 0; i < enemy->size(); i++)
    {
        enemy->at(i).init();
        enemy->at(i).loadGraphic("ZELDA/Sprites/Enemies/blue_enemy.png");
        enemy->at(i).setGraphicID();
        enemy->at(i).setWH(16, 16);                // w-h de cada sprite
        enemy->at(i).setXY(0, 0);                  // x-y del sprite
        enemy->at(i).setLife(2);

        int rndX = rand() % 2304;
        int rndY = rand() % 480;
        while (mapa->getTileID(rndX / 16, rndY / 16) != 3)
        {
            rndX = rand() % 2304;
            rndY = rand() % 480;
        }
        enemy->at(i).setWorldXY(rndX, rndY);
    }
}
void SceneGame::worldCollisionEnemies(vector<Enemy>* enemy)
{
    for (unsigned int i = 0; i < enemy->size(); i++)
    {
        enemy->at(i).worldCollision();
    }
}
void SceneGame::updateEnemies(vector<Enemy>* enemy)
{
    for (unsigned int i = 0; i < enemy->size(); i++)
    {
        enemy->at(i).update();
    }
}
void SceneGame::enemyCollision(vector<Enemy>* enemy)
{
    int _FrameRate = 600;
    for (unsigned int i = 0; i < enemy->size(); i++)
    {
        if (!enemy->at(i).isDead())
        {

            if (_Player.isCollision(_Player.getRect(), enemy->at(i).getRect()))
            {
                if (_FrameTime > _FrameRate)
                {
                    sound->playSound(_DamageSound, "ZELDA/Sound/FX/recieve-damage.ogg", 0);
                    sound->setSoundVolume(_DamageSound, 30);
                    int life = _Player.getLife();
                    life--;
                    _Player.setLife(life);
                    _FrameTime = 0;
                }
            }
        }
    }
}
void SceneGame::renderEnemy(vector<Enemy>* enemy)
{
    for (unsigned int i = 0; i < enemy->size(); i++)
    {
        enemy->at(i).render(enemy->at(i).getSpriteX(), enemy->at(i).getSpriteY());
    }
}

// RUPEES
void SceneGame::initRupees(vector<Object>* rupee)
{
    rupee->resize(10 + (rand() % 5));
    for (unsigned int i = 0; i < rupee->size(); i++)
    {
        rupee->at(i).loadGraphic("ZELDA/Sprites/LinkAndObjects/rupee.png");
        rupee->at(i).setGraphicID();
        rupee->at(i).setWH(16, 16);                // w-h de cada sprite
        rupee->at(i).setXY(0, 0);                  // x-y del sprite
        rupee->at(i).setHitten(false);

        int rndX = rand() % 2304;
        int rndY = rand() % 480;
        while (mapa->getTileID(rndX/16, rndY/16) != 3)
        {
            rndX = rand() % 2304;
            rndY = rand() % 480;
        }
        rupee->at(i).setWorldXY(rndX, rndY);
    }
}
void SceneGame::worldCollisionRupees(vector<Object>* rupee)
{
    for (unsigned int i = 0; i < rupee->size(); i++)
    {
        rupee->at(i).worldCollision();
    }
}
void SceneGame::rupeeCollision(vector<Object>* rupee)
{
    int _FrameRate = 200;
    for (unsigned int i = 0; i < rupee->size(); i++)
    {
        if (_Player.isCollision(_Player.getRect(), rupee->at(i).getRect()))
        {
            if (!rupee->at(i).getHitten())
            {
                if (_FrameTime > _FrameRate)
                {
                    sound->playSound(_CoinSound, "ZELDA/Sound/FX/coin.ogg", 0);
                    sound->setSoundVolume(_CoinSound, 30);
                    rupee->at(i).setHitten(true);
                    int coin = _Player.getRupees();
                    coin++;
                    _Player.setRupees(coin);
                    _FrameTime = 0;
                }
            }
        }
    }
}
void SceneGame::renderRupees(vector<Object>* rupee)
{
    for (unsigned int i = 0; i < rupee->size(); i++)
    {
        rupee->at(i).render();
    }
}

// HEARTS
void SceneGame::initHearts(vector<Object>* heart)
{
    heart->resize(5);
    for (unsigned int i = 0; i < heart->size(); i++)
    {
        heart->at(i).loadGraphic("ZELDA/Sprites/LinkAndObjects/heart.png");
        heart->at(i).setGraphicID();
        heart->at(i).setWH(16, 16);                // w-h de cada sprite
        heart->at(i).setXY(0, 0);                  // x-y del sprite
        heart->at(i).setHitten(false);
    }
    heart->at(0).setWorldXY(92*16, 52*16);
    heart->at(1).setWorldXY(35*16, 33*16);
    heart->at(2).setWorldXY(87*16, 5*16);
    heart->at(3).setWorldXY(139*16, 16*16);
    heart->at(4).setWorldXY(110*16, 44*16);
}
void SceneGame::heartCollision(vector<Object>* heart)
{
    int _FrameRate = 200;
    for (unsigned int i = 0; i < heart->size(); i++)
    {
        if (_Player.isCollision(_Player.getRect(), heart->at(i).getRect()))
        {
            if (!heart->at(i).getHitten())
            {
                if (_FrameTime >= _FrameRate)
                {
                    sound->playSound(_CoinSound, "ZELDA/Sound/FX/coin.ogg", 0);
                    sound->setSoundVolume(_CoinSound, 30);
                    heart->at(i).setHitten(true);
                    int life = _Player.getMaxLife();
                    life += 2;
                    _Player.setMaxLife(life);
                    _Player.setLife(life);
                    _FrameTime = 0;
                }
            }
        }
    }
}
void SceneGame::renderheart(vector<Object>* heart)
{
    for (unsigned int i = 0; i < heart->size(); i++)
    {
        heart->at(i).render();
    }
}

// TRIFORCE PIECES
void SceneGame::triforceCollision(Object* triforce)
{
    int _FrameRate = 200;
    if (_Player.isCollision(_Player.getRect(), triforce->getRect()))
    {
        if (!triforce->getHitten())
        {
            if (_FrameTime >= _FrameRate)
            {
                sound->playSound(_TFSound, "ZELDA/Sound/Music/Triforce.ogg", 0);
                sound->setSoundVolume(_TFSound, 30);
                triforce->setHitten(true);
                int tfp = _Player.getTriforcePieces();
                tfp++;
                _Player.setTriforcePieces(tfp);
                _FrameTime = 0;
            }
        }
    }
}
void SceneGame::renderTriforce(Object* triforce)
{
    triforce->render();
}
