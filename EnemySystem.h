#pragma once
#include "TinyDemon.h"
#include "Demon.h"
#include "HugeDemon.h"
#include "Summoner.h"
#include "Player.h"
#include "Wizzard.h"
#include <queue>
#include "BonusComponent.h"
#include "Data.h"

enum EnemyType
{
	Tiny,
	Medium,
	Huge,
	Summonerr,
	Wizzardd
};

struct waveInfo
{
	int countEnemies;
	float modificatorProbabilty;
	int scoreLimit;
	map<int, pair<float, float>> probabilites;
};


class EnemySystem
{
private:
	void initWaveInfo();

	sfxData* sfx;
	Settings* settings;
	Texture* texture;


	queue<Enemy*> enemies;
	Enemy* currentEnemy;
	Player* player;
	queue<queue<Fireball*>*>* fireballs;
	BonusComponent* bonus;
	ShootComponent* shootComponent;

	vector<waveInfo> spawnController;
	waveInfo waveData;

	Vector2f targetPos;
	Vector2f spawnPos;


	Clock spawnTimer;
	Clock waveTimer;

	int countSpawned;

	float spawnTime;
	float waveTime;

	bool waveEnd;
	int wave;

	
	float* score;
	float spawnRadius;
public:
	EnemySystem(Player * player, float * score, Texture * texture, BonusComponent* bonus);
	~EnemySystem();

	queue<Enemy*>* getEnemies();
	Enemy * newEnemy;

	void setTarget(Vector2f pos);
	void setFireballs(queue<queue<Fireball*>*>* fireballs);
	void setSfx(sfxData* data);
	void setSettings(Settings* settings);

	int getWaveNumber();
	waveInfo getWaveInfo();

	void generateSpawnPos();
	bool generateModificator(float prob);
	bool checkCooldown();
	void spawn();
	string getModificator(int type);

	void update(const float& dt);
	void spawnUpdate();
	void render(RenderTarget* target = nullptr);

};

