#pragma once
#include "Enemy.h"
class TinyDemon :
    public Enemy
{
private:

public:
    float velocityMultiplier;
    TinyDemon(float x, float y, Texture* texture, IntRect pos, float scale = 5.f);
    ~TinyDemon();
    void update(const float& dt, Vector2f targetPos);

    void initEntityProperty();

    void setModificator(string key);
};

