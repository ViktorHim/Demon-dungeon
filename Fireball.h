#pragma once
#include "Entity.h"
#include "DataPaths.h"
#include <cmath>
#define PI 3.1415926535
class Fireball
{
private:
	Sprite* sprite;
	Texture* texture;
	IntRect pos;

	float damage;
	Clock lifeTimeClock;
	float lifeTime;
	float velocity;
	float rotation;

	Vector2f direction;
	float length;
public:
	Fireball(Vector2f playerPos, Vector2f mousePos, float damage, Texture* texture, IntRect pos, IntRect playerSize, float velocity);
	~Fireball();
	bool isEnd;
	 const Vector2f& getPosition() const;
	 const Vector2i& getGridPosition(const int gridSize) const;
	 FloatRect * getGlobalBounds();
	 bool isCollision(FloatRect rect);
	void update(const float& dt);
	void setColor(Color);
	float getDamage();
	void createSprite(Texture* texture);
	void render(RenderTarget* target = nullptr);
};

