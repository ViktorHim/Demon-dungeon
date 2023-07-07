#include "EnemySystem.h"

void EnemySystem::initWaveInfo()
{
	spawnController.push_back(
		waveInfo
		{
			2,
			0.f,
			250,
			{
				{Tiny, pair<float, float>(0, 100)}
			}
		}
	);

	spawnController.push_back(
		waveInfo
		{
			3,
			3.f,
			500,
			{
				{Tiny, pair<float, float>(0, 90)},
				{ Medium, pair<float, float>(91, 100)}
			}
		}
	);

	spawnController.push_back(
		waveInfo
		{
			3,
			5.f,
			1000,
			{
				{Tiny, pair<float, float>(0, 80)},
				{ Medium, pair<float, float>(81, 100)}
			}
		}
	);

	spawnController.push_back(
		waveInfo
		{
			4,
			10.f,
			1500,
			{
				{Tiny, pair<float, float>(0, 70)},
				{Medium, pair<float, float>(71, 95)},
				{Huge, pair<float, float>(96, 100)}
			}
		}
	);

	spawnController.push_back(
		waveInfo
		{
			5,
			15.f,
			4000,
			{
				{Tiny, pair<float, float>(0, 50)},
				{Medium, pair<float, float>(51, 70)},
				{Huge, pair<float, float>(71, 80)},
				{Summonerr, pair<float, float>(81, 90)},
				{Wizzardd, pair<float, float>(91, 100)}
			}
		}
	);

	spawnController.push_back(
		waveInfo
		{
			7,
			15.f,
			7000,
			{
				{Tiny, pair<float, float>(0, 45)},
				{Medium, pair<float, float>(46, 65)},
				{Huge, pair<float, float>(66, 75)},
				{Summonerr, pair<float, float>(76, 85)},
				{Wizzardd, pair<float, float>(86, 100)}
			}
		}
	);

	spawnController.push_back(
		waveInfo
		{
			8,
			20.f,
			10000,
			{
				{Tiny, pair<float, float>(0, 40)},
				{Medium, pair<float, float>(41, 65)},
				{Huge, pair<float, float>(66, 75)},
				{Summonerr, pair<float, float>(76, 85)},
				{Wizzardd, pair<float, float>(86, 100)}
			}
		}
	);

	spawnController.push_back(
		waveInfo
		{
			10,
			30.f,
			12000,
			{
				{Tiny, pair<float, float>(0, 30)},
				{Medium, pair<float, float>(31, 55)},
				{Huge, pair<float, float>(56, 65)},
				{Summonerr, pair<float, float>(66, 75)},
				{Wizzardd, pair<float, float>(76, 100)}
			}
		}
	);

	spawnController.push_back(
		waveInfo
		{
			12,
			40.f,
			16000,
			{
				{Tiny, pair<float, float>(0, 20)},
				{Medium, pair<float, float>(21, 45)},
				{Huge, pair<float, float>(46, 65)},
				{Summonerr, pair<float, float>(66, 75)},
				{Wizzardd, pair<float, float>(76, 100)}
			}
		}
	);
	
	spawnController.push_back(
		waveInfo
		{
			14,
			70.f,
			24000,
			{
				{Tiny, pair<float, float>(0, 15)},
				{Medium, pair<float, float>(16, 45)},
				{Huge, pair<float, float>(46, 65)},
				{Summonerr, pair<float, float>(66, 75)},
				{Wizzardd, pair<float, float>(76, 100)}
			}
		}
	);
	
}

EnemySystem::EnemySystem(Player* player, float* score, Texture * texture, BonusComponent* bonus)
{
	this->sfx = nullptr;
	this->settings = nullptr;
	this->bonus = bonus;
	this->shootComponent = shootComponent;
	this->player = player;
	this->score = score;
	this->texture = texture;
	this->fireballs = nullptr;
	waveTime = 5.f;
	wave = 0;
	currentEnemy = nullptr;
	waveEnd = true;
	spawnRadius = 450.f;
	spawnTime = 0.5f;
	countSpawned = 0;

	initWaveInfo();

}

EnemySystem::~EnemySystem()
{

}

queue<Enemy*>* EnemySystem::getEnemies()
{
	return &enemies;
}

void EnemySystem::setTarget(Vector2f pos)
{
}

void EnemySystem::setFireballs(queue<queue<Fireball*>*>* fireballs)
{
	this->fireballs = fireballs;
}

void EnemySystem::setSfx(sfxData* data)
{
	this->sfx = data;
}

void EnemySystem::setSettings(Settings* settings)
{
	this->settings = settings;
}

void EnemySystem::generateSpawnPos()
{
	float randX;
	float randY;
	Vector2f playerPos = player->getPosition();
	
		randX = rand() % 2000 + 100;
		if (randX >= playerPos.x - spawnRadius && randX <= playerPos.x)
		{
			if (playerPos.x - spawnRadius <= 100)
			{
				randX = playerPos.x + spawnRadius;
			}
			else
			{
				randX = playerPos.x - spawnRadius;
			}
		}
		else if (randX <= playerPos.x + spawnRadius && randX >= playerPos.x)
		{
			if (playerPos.x + spawnRadius >= 2100)
			{
				randX = playerPos.x - spawnRadius;
			}
			else
			{
				randX = playerPos.x + spawnRadius;
			}
		}


		randY = rand() % 2000 + 100;
		if (randY >= playerPos.y - spawnRadius && randY <= playerPos.y)
		{
			if (playerPos.y - spawnRadius <= 100)
			{
				randY = playerPos.y + spawnRadius;
			}
			else
			{
				randY = playerPos.y - spawnRadius;
			}
		}
		else if (randY <= playerPos.y + spawnRadius && randX >= playerPos.y)
		{
			if (playerPos.y + spawnRadius >= 2100)
			{
				randY = playerPos.y - spawnRadius;
			}
			else
			{
				randY = playerPos.y + spawnRadius;
			}
		}

	spawnPos =  Vector2f(randX, randY);
}

bool EnemySystem::generateModificator(float prob)
{
	if (prob != 0 && rand() % 101 <= prob)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool EnemySystem::checkCooldown()
{
	if (spawnTimer.getElapsedTime().asSeconds() >= spawnTime)
	{
		spawnTimer.restart();
		return true;
	}

	return false;
}

void EnemySystem::spawn()
{
	int randValue = rand() % 101;
	for (auto& i : waveData.probabilites)
	{
		if (randValue >= i.second.first && randValue <= i.second.second)
		{
			generateSpawnPos();
			switch (i.first)
			{
			case Tiny:
			{
				TinyDemon* demon = new TinyDemon(spawnPos.x, spawnPos.y, texture, TINY_DEMON_START);
				demon->setModificator(getModificator(Tiny));
				demon->setSfx(sfx);
				demon->setSettings(settings);
				enemies.push(demon);
			}break;
			case Medium:
			{
				Demon* demon = new Demon(spawnPos.x, spawnPos.y, texture, DEMON_START);
				demon->setModificator(getModificator(Medium));
				demon->setSfx(sfx);
				demon->setSettings(settings);
				enemies.push(demon);

			} break;
			case Huge:
			{
				HugeDemon* demon = new HugeDemon(spawnPos.x, spawnPos.y, texture, HUGE_DEMON_START);
				demon->setModificator(getModificator(Huge));
				demon->setSfx(sfx);
				demon->setSettings(settings);
				enemies.push(demon);
			}break;
			case Summonerr:
			{
				Summoner* summoner = new Summoner(spawnPos.x, spawnPos.y, texture, SUMMONER_DEMON_START, &enemies);
				summoner->setSfx(sfx);
				summoner->setSettings(settings);
				enemies.push(summoner);
			}break;
			case Wizzardd:
			{
				Wizzard* wiz = new Wizzard(spawnPos.x, spawnPos.y, texture, WIZZARD_START);
				queue<Fireball*>* bullets = new queue<Fireball*>;
				fireballs->push(bullets);
				wiz->shootComponent->setTarget(player);
				wiz->shootComponent->setFireballs(bullets);
				wiz->setModificator(getModificator(Wizzardd));
				wiz->setSfx(sfx);
				wiz->setSettings(settings);
				enemies.push(wiz);
			}break;
			}
		}
	}
}

string EnemySystem::getModificator(int type)
{
	switch (type)
	{
		case Tiny: 
		{
			if (generateModificator(waveData.modificatorProbabilty) && *score >= 1500)
			{
				if (*score >= 5000)
				{
					return "faster";
				}
				else
				{
					return "fast";
				}
			}
		} break;
		case Medium:
		{
			if (generateModificator(waveData.modificatorProbabilty) && *score >= 5000)
			{
				if (*score >= 8000)
				{
					return "strongest";
				}
				else
				{
					return "stronger";
				}
			}
		} break;
		case Huge:
		{
			if (generateModificator(waveData.modificatorProbabilty) && *score >= 7000)
			{
				if (*score >= 10000)
				{
					return "strongest";
				}
				else
				{
					return "stronger";
				}
			}

		} break;
		case Wizzardd:
		{
			if (generateModificator(waveData.modificatorProbabilty) && *score >= 7000)
			{
				if (*score >= 20000)
				{
					return "dark";
				}
				else
				{
					return "founder";
				}
			}

		} break;
	}

	return "none";
}

int EnemySystem::getWaveNumber()
{
	return wave;
}

waveInfo EnemySystem::getWaveInfo()
{
	for (auto i : spawnController)
	{
		if (*score < i.scoreLimit)
		{
			return i;
		}
	}
}

void EnemySystem::update(const float& dt)
{
	spawnUpdate();

	if (enemies.empty() && wave > 0 && countSpawned == waveData.countEnemies)
	{
		waveEnd = true;
	}

	for (int i = 0; i < enemies.size(); i++)
	{
		currentEnemy = enemies.front();
		enemies.pop();
		if (currentEnemy->isAlive)
		{
			currentEnemy->update(dt, player->getPosition());
			if (currentEnemy->isCollision(player->getGlobalBounds()))
			{
				player->setDamage(currentEnemy->getDamage());
			}
			enemies.push(currentEnemy);
		}
		else
		{
			*score += currentEnemy->getScore();
			delete currentEnemy;
		}
	}
}

void EnemySystem::spawnUpdate()
{
	if (waveTimer.getElapsedTime().asSeconds() >= waveTime && waveEnd)
	{
		waveTimer.restart();
		waveEnd = false;
		wave++;
		waveData = getWaveInfo();
		countSpawned = 0;

		if (wave % 5 == 0 && wave > 0)
		{
			bonus->spawnPotion("health");
		}
	}

	if (countSpawned < waveData.countEnemies && checkCooldown())
	{
		spawn();
		countSpawned++;
	}
}

void EnemySystem::render(RenderTarget* target)
{
	for (int i = 0; i < enemies.size(); i++)
	{
		currentEnemy = enemies.front();
		enemies.pop();
		currentEnemy->render(target);
		enemies.push(currentEnemy);
	}
}