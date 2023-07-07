#include "HealthPotion.h"
#include "ManaPotion.h"
#include "DoubleShootPotion.h"
#include "TripleShootPotion.h"
#include "SpeedPotion.h"
#include "Player.h"
#include "TileMap.h"
#include "Data.h"
#pragma once
class BonusComponent
{
private:
	sfxData* sfx;
	Settings* settings;

	TileMap* tileMap;
	Player* target;
	queue<Potion *> potions;
	Potion* currentPotion;
	Texture* texture;
	int maxSize;

	Clock spawnCooldownTimer;
	float spawnCooldownTime;

	map<string, float> remainingTime;
	float doubleShootTime;
	float tripleShootTime;
public:
	BonusComponent(Player* target, Texture * texture, TileMap * tileMap);
	~BonusComponent();
	float getTripleShootTime();
	float getDoubleShootTime();
	map<string, float>* getRemainingTime();

	void setSfx(sfxData* data);
	void setSettings(Settings* settings);
	//обновление
	void update(const float& dt);
	void spawnUpdate();
	void spawnPotion(string key);
	//рендер
	void render(RenderTarget* target = nullptr);
};

