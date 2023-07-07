#pragma once
#include "ShootComponent.h"
class Wizzard :
    public Enemy
{
private:

public:
    ShootComponent* shootComponent;

    float velocityMultiplier;
    Wizzard(float x, float y, Texture* texture, IntRect pos, float scale = 5.f);
    ~Wizzard();

    void setSfx(sfxData* data);
    void setSettings(Settings* settings);

    void update(const float& dt, Vector2f targetPos);
    void move(const float& dt, Vector2f targetPos);
   void render(RenderTarget* target = nullptr);

    void initEntityProperty();

    void setModificator(string key);
};

