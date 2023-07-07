#pragma once
#include "Entity.h"
#include "ProgressBar.h"

#define DEMON_START IntRect(370, 278, 16, 17)
#define TINY_DEMON_START IntRect(370, 68, 15, 11)
#define HUGE_DEMON_START IntRect(16, 434, 32, 29)
#define SUMMONER_DEMON_START IntRect(370, 256, 16, 17)
#define WIZZARD_START IntRect(369, 231, 16, 17)

class Enemy :
    public Entity
{
protected:
public:
    Vector2f direction;
    float length;
    float dx;
    float dy;
    ProgressBar* healthBar;
    Vector2f targetPos;
    bool follow;

    Enemy(float x, float y, Texture* texture, IntRect pos, float scale = 5.f);
    virtual ~Enemy();
    virtual void initEntityProperty();
    void setTarget(Vector2f  targetPos);
    bool getFollow();
    Vector2i getVelocity();
    void setFollow(bool);
    virtual void update(const float& dt, Vector2f targetPos);
    virtual void move(const float& dt, Vector2f targetPos);
    virtual void render(RenderTarget* target = nullptr);
};