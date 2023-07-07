#pragma once
#include "Enemy.h"
class HugeDemon :
    public Enemy
{
private:

public:
    float velocityMultiplier;
    float healthMultiplier;
    float damageMultiplier;
    HugeDemon(float x, float y, Texture* texture, IntRect pos, float scale = 5.f);
    ~HugeDemon();
    void initEntityProperty();
    void update(const float& dt, Vector2f targetPos);

    void setModificator(string key);

};

