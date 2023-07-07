#include "BonusComponent.h"

BonusComponent::BonusComponent(Player* target, Texture * texture, TileMap * tileMap)
{
	this->sfx = nullptr;
	this->settings = nullptr;
	this->tileMap = tileMap;
	this->texture = texture;
	this->target = target;
	maxSize = 3;
	currentPotion = nullptr;
	spawnCooldownTime = 10.f;
	tripleShootTime = 0.0f;
	doubleShootTime = 0.0f;
}

BonusComponent::~BonusComponent()
{
}

float BonusComponent::getTripleShootTime()
{
	return tripleShootTime;
}

float BonusComponent::getDoubleShootTime()
{
	return doubleShootTime;
}

map<string, float>* BonusComponent::getRemainingTime()
{
	return &remainingTime;
}

void BonusComponent::setSfx(sfxData* data)
{
	this->sfx = data;
}

void BonusComponent::setSettings(Settings* settings)
{
	this->settings = settings;
}

void BonusComponent::update(const float& dt)
{
	spawnUpdate();

	float maxTriple = 0;
	float maxDouble = 0;
	float maxSpeed = 0;
	for (int i = 0; i < potions.size(); i++)
	{
		

		currentPotion = potions.front();
		potions.pop();

		if (currentPotion != nullptr && (currentPotion->isActive() || !currentPotion->isPickedUp()))
		{
			currentPotion->update(dt);

			if (currentPotion->getTag() == "triple" && currentPotion->getRemainingTime() > maxTriple)
			{
				maxTriple = currentPotion->getRemainingTime();
			}
			else if (currentPotion->getTag() == "double" && currentPotion->getRemainingTime() > maxDouble)
			{
				maxDouble = currentPotion->getRemainingTime();

			}
			else if (currentPotion->getTag() == "speed" && currentPotion->getRemainingTime() > maxSpeed)
			{
				maxSpeed = currentPotion->getRemainingTime();
			}
			potions.push(currentPotion);
		}
		else
		{
			delete currentPotion;
		}

	}
	remainingTime["triple"] = maxTriple;
	remainingTime["double"] = maxDouble;
	remainingTime["speed"] = maxSpeed;



}

void BonusComponent::spawnUpdate()
{
	if (spawnCooldownTimer.getElapsedTime().asSeconds() >= spawnCooldownTime)
	{
		spawnCooldownTimer.restart();

		if (potions.size() < maxSize)
		{
			int random = rand() % 5;
			float x = rand() % 50;
			float y = rand() % 50;

			if (!tileMap->isFreeTile(x, y))
			{
				x = 25;
				y = 25;
			}


			switch (random)
			{
			case 1:
			{
				Potion* potion = new ManaPotion(target, texture, x * 48, y * 48);
				potion->setSettings(settings);
				potion->setSfx(sfx);
				potions.push(potion);

			} break;
			case 2:
			{
				DoubleShootPotion* potion = new DoubleShootPotion(target, texture, x * 48, y * 48);
				potion->setSettings(settings);
				potion->setSfx(sfx);
				potions.push(potion);

			} break;
			case 3:
			{
				TripleShootPotion* potion = new TripleShootPotion(target, texture, x * 48, y * 48);
				potion->setSettings(settings);
				potion->setSfx(sfx);
				potions.push(potion);

			} break;
			case 4:
			{
				SpeedPotion* potion = new SpeedPotion(target, texture, x * 48, y * 48);
				potion->setSettings(settings);
				potion->setSfx(sfx);
				potions.push(potion);

			} break;
			}
		}
	}
}

void BonusComponent::spawnPotion(string key)
{
	int random = rand() % 5;
	float x = rand() % 50;
	float y = rand() % 50;

	if (!tileMap->isFreeTile(x, y))
	{
		x = 25;
		y = 25;
	}

	if (key == "health")
	{
		Potion* potion = new HealthPotion(target, texture, x * 48, y * 48);
		potion->setSettings(settings);
		potion->setSfx(sfx);
		potions.push(potion);
	}
}

void BonusComponent::render(RenderTarget* target)
{
	for (int i = 0; i < potions.size(); i++)
	{
		currentPotion = potions.front();
		potions.pop();
		currentPotion->render(target);

		if (currentPotion != nullptr && (currentPotion->isActive() || !currentPotion->isPickedUp()))
		{
		}
		potions.push(currentPotion);

	}

}
