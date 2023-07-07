#pragma once
#include "DataPaths.h"
#include "Fireball.h"
#include <list>
#include <queue>
#include "Enemy.h"
#include "Data.h"

//#include "Player.h"

#define FIREBALL IntRect(299, 299, 15, 8)



class ShootComponent
{
private:
	sfxData * sfx;
	Settings* settings;

	queue<Fireball*>* fireballs;
	queue<Enemy*>* demons;
	Entity* player;

	Enemy* currentEnemy;
	Fireball* currentFireball;
	Texture texture;
	Clock timer;

	IntRect playerSize;
	IntRect pos;

	float value;
	float damage;
	float shootCooldown;
	float velocity;
	float crit;

	Color color;

public:
	ShootComponent(float shootCooldown, float velocity, float damage, IntRect pos, IntRect playerSize);
	~ShootComponent();

	void setFireballs(queue<Fireball*>* fireballs);
	void setTargets(queue<Enemy*>* demons);
	void setTarget(Entity * player);
	void setColor(Color color);

	void setCrit(float crit);
	void setDamage(float damage);
	void setVelocity(float velocity);
	void setCooldown(float cooldown);

	void setSfx(sfxData * data);
	void setSettings(Settings* settings);

	void playSound();

	bool addFireball(Vector2f playerPos, Vector2f mousePos);
	bool addFireball(Vector2f playerPos, Vector2f mousePos, float k);
	bool addTripleFireball(Vector2f playerPos, Vector2f mousePos);
	bool addTripleFireball(Vector2f playerPos, Vector2f mousePos, float k);


	void collisionUpdate(Fireball* fireball);

	void update(Vector2f* mousePosView, const float& dt);
	void render(RenderTarget* target = nullptr);
};

