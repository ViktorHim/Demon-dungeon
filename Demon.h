#pragma once
#include "Enemy.h"

class Demon: public Enemy
{
private:

public:
    float velocityMultiplier;
    float damageMultiplier;
    Demon(float x, float y, Texture* texture, IntRect pos, float scale = 5.f);
    ~Demon();
    void update(const float& dt, Vector2f targetPos);
    void initEntityProperty();
    void setModificator(string key);

};

