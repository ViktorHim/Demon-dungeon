#pragma once
#include "Enemy.h"
#include "TinyDemon.h"
#include <queue>
class Summoner :
    public Enemy
{
private:
    queue<Enemy*>* enemies;
    Clock spawnCooldown;
    float time;
public:

    Summoner(float x, float y, Texture* texture, IntRect pos, queue<Enemy*>* enemies, float scale = 5.f);
    ~Summoner();
    void update(const float& dt, Vector2f targetPos);
    void initEntityProperty();
    void spawn();
};

