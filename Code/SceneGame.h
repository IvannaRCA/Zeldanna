#pragma once
#include <vector>
#include "Scene.h"
#include "HUD.h"
#include "Map.h"
#include "Player.h"
#include "Enemy.h"
#include "Object.h"

class SceneGame :
    public Scene
{
    HUD _HUD;
    Player _Player;
    std::vector <Enemy> _RedEnemy;
    std::vector <Enemy> _BlueEnemy;
    std::vector <Object> _Rupee;
    std::vector <Object> _Heart;
    Object _Sword;
    Object _TF1;
    Object _TF2;
    Object _TF3;
    int _FrameTime;
    int _DamageSound;
    int _SwordSound;
    int _CoinSound;
    int _TFSound;
public:
    void reinit();
    void init();
    void update();
    void render();

    void playerAttack(vector <Enemy>* enemy);

    void initRedEnemy(vector <Enemy>* enemy);
    void initBlueEnemy(vector <Enemy>* enemy);
    void worldCollisionEnemies(vector <Enemy>* enemy);
    void updateEnemies(vector <Enemy>* enemy);
    void enemyCollision(vector<Enemy>* enemy);
    void renderEnemy(vector <Enemy>* enemy);
    
    void initRupees(vector <Object>* rupee);
    void worldCollisionRupees(vector <Object>* rupee);
    void rupeeCollision(vector<Object>* rupee);
    void renderRupees(vector <Object>* rupee);

    void initHearts(vector <Object>* heart);
    void heartCollision(vector<Object>* heart);
    void renderheart(vector <Object>* heart);

    void triforceCollision(Object* triforce);
    void renderTriforce(Object* triforce);
};

