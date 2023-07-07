#include "ShootComponent.h"

ShootComponent::ShootComponent(float shootCooldown, float velocity, float damage, IntRect pos, IntRect playerSize)
{
	this->sfx = nullptr;
	this->settings = nullptr;
	this->shootCooldown = shootCooldown;
	this->velocity = velocity;
	this->damage = damage;
	this->pos = pos;
	this->playerSize = playerSize;
	this->value = 10.f;
	this->demons = nullptr;
	this->player = nullptr;
	this->currentEnemy = nullptr;
	this->currentFireball = nullptr;
	this->fireballs = nullptr;
	this->texture.loadFromFile(PROJECTILES);
	this->color = Color(255, 255, 255, 255);
	this->crit = 0.f;
}

ShootComponent::~ShootComponent()
{
}




void ShootComponent::setFireballs(queue<Fireball*>* fireballs)
{
	this->fireballs = fireballs;
}

void ShootComponent::setTargets(queue<Enemy*>* demons)
{
	this->demons = demons;
}

void ShootComponent::setTarget(Entity * player)
{
	this->player = player;
}

void ShootComponent::setColor(Color color)
{
	this-> color = color;
}

void ShootComponent::setCrit(float crit)
{
	this->crit = crit;
}

void ShootComponent::setDamage(float damage)
{
	this->damage = damage;
}

void ShootComponent::setVelocity(float velocity)
{
	this->velocity = velocity;
}

void ShootComponent::setCooldown(float cooldown)
{
	this->shootCooldown = cooldown;
}

void ShootComponent::setSfx(sfxData* data)
{
	this->sfx = data;
}

void ShootComponent::setSettings(Settings* settings)
{
	this->settings = settings;
}

void ShootComponent::playSound()
{
	if (sfx && settings && settings->sfx)
	{
		sfx->sounds[sounds::fireball].play();
	}
}

bool ShootComponent::addFireball(Vector2f playerPos, Vector2f mousePos)
{
	if (timer.getElapsedTime().asSeconds() >= shootCooldown)
	{
		int critChance = 0;
		critChance = rand() % 101;
		if (critChance < crit)
		{
			Fireball* fireball = new Fireball(playerPos, mousePos, 2 * damage, &texture, pos, playerSize, velocity);
			fireball->setColor(Color(3, 231, 252, 255));
			fireballs->push(fireball);
		}
		else
		{
			Fireball* fireball = new Fireball(playerPos, mousePos,  damage, &texture, pos, playerSize, velocity);
			fireball->setColor(color);		
			fireballs->push(fireball);
		}

		timer.restart();
		playSound();
		return true;
	}
	return false;

}

bool ShootComponent::addFireball(Vector2f playerPos, Vector2f mousePos, float k)
{
	if (timer.getElapsedTime().asSeconds() >= shootCooldown / k)
	{
		int critChance = 0;
		critChance = rand() % 101;
		if (critChance < crit)
		{
			Fireball* fireball = new Fireball(playerPos, mousePos, 2 * damage, &texture, pos, playerSize, velocity);
			fireball->setColor(Color(3, 231, 252, 255));
			fireballs->push(fireball);
		}
		else
		{
			Fireball* fireball = new Fireball(playerPos, mousePos, damage, &texture, pos, playerSize, velocity);
			fireball->setColor(color);
			fireballs->push(fireball);
		}

		timer.restart();
		playSound();

		return true;
	}

	return false;
}

bool ShootComponent::addTripleFireball(Vector2f playerPos, Vector2f mousePos)
{
	if (timer.getElapsedTime().asSeconds() >= shootCooldown)
	{
		Vector2f leftMouse = Vector2f(mousePos.x - 100, mousePos.y - 100);
		Vector2f rightMouse = Vector2f(mousePos.x + 100, mousePos.y + 100);

	
		int critChance = 0;
		critChance = rand() % 101;
		if (critChance < crit)
		{
			Fireball* fireball = new Fireball(playerPos, mousePos, 2 * damage, &texture, pos, playerSize, velocity);
			fireball->setColor(Color(3, 231, 252, 255));
			fireballs->push(fireball);

			fireball = new Fireball(playerPos, leftMouse, damage, &texture, pos, playerSize, velocity - 10);
			fireball->setColor(color);
			fireballs->push(fireball);

			fireball = new Fireball(playerPos, rightMouse, damage, &texture, pos, playerSize, velocity - 10);
			fireball->setColor(color);
			fireballs->push(fireball);
		}
		else
		{
			Fireball* fireball = new Fireball(playerPos, mousePos, damage, &texture, pos, playerSize, velocity);
			fireball->setColor(color);
			fireballs->push(fireball);

			fireball = new Fireball(playerPos, leftMouse, damage, &texture, pos, playerSize, velocity - 10);
			fireball->setColor(color);
			fireballs->push(fireball);

			fireball = new Fireball(playerPos, rightMouse, damage, &texture, pos, playerSize, velocity - 10);
			fireball->setColor(color);
			fireballs->push(fireball);
		}

		timer.restart();
		playSound();

		return true;
	}
	return false;
}

bool ShootComponent::addTripleFireball(Vector2f playerPos, Vector2f mousePos, float k)
{
	if (timer.getElapsedTime().asSeconds() >= shootCooldown / k)
	{
		Vector2f leftMouse = Vector2f(mousePos.x - 100, mousePos.y - 100);
		Vector2f rightMouse = Vector2f(mousePos.x + 100, mousePos.y + 100);


		int critChance = 0;
		critChance = rand() % 101;
		if (critChance < crit)
		{
			Fireball* fireball = new Fireball(playerPos, mousePos, 2 * damage, &texture, pos, playerSize, velocity);
			fireball->setColor(Color(3, 231, 252, 255));
			fireballs->push(fireball);

			fireball = new Fireball(playerPos, leftMouse, damage, &texture, pos, playerSize, velocity - 10);
			fireball->setColor(color);
			fireballs->push(fireball);

			fireball = new Fireball(playerPos, rightMouse, damage, &texture, pos, playerSize, velocity - 10);
			fireball->setColor(color);
			fireballs->push(fireball);
		}
		else
		{
			Fireball* fireball = new Fireball(playerPos, mousePos, damage, &texture, pos, playerSize, velocity);
			fireball->setColor(color);
			fireballs->push(fireball);

			fireball = new Fireball(playerPos, leftMouse, damage, &texture, pos, playerSize, velocity - 10);
			fireball->setColor(color);
			fireballs->push(fireball);

			fireball = new Fireball(playerPos, rightMouse, damage, &texture, pos, playerSize, velocity - 10);
			fireball->setColor(color);
			fireballs->push(fireball);
		}

		timer.restart();
		playSound();

		return true;
	}
	return false;
}


void ShootComponent::collisionUpdate(Fireball* fireball)
{
	if (demons)
	{
		for (int i = 0; i < demons->size(); i++)
		{
			currentEnemy = demons->front();
			demons->pop();

			if (currentEnemy != nullptr && currentEnemy->isAlive && !fireball->isEnd)
			{
				if (fireball->isCollision(currentEnemy->getGlobalBounds()))
				{
					currentEnemy->setDamage(fireball->getDamage());
					fireball->isEnd = true;
				}
			}
			
			demons->push(currentEnemy);
		}
	}
	if (player)
	{
		if (fireball->isCollision(player->getGlobalBounds()))
		{
			player->setInstanceDamage(fireball->getDamage());
			fireball->isEnd = true;
		}
	}
	

}

void ShootComponent::update(Vector2f* mousePosView, const float& dt)
{
	if (fireballs)
	{
		for (int i = 0; i < fireballs->size(); i++)
		{
			currentFireball = fireballs->front();
			fireballs->pop();

			if (!currentFireball->isEnd)
			{
				currentFireball->update(dt);
				collisionUpdate(currentFireball);
				fireballs->push(currentFireball);
			}
			else
			{
				delete currentFireball;
				currentFireball = nullptr;
			}
		}
	}
}

void ShootComponent::render(RenderTarget* target)
{
	for (int i = 0; i < fireballs->size(); i++)
	{
		currentFireball = fireballs->front();
		fireballs->pop();

		if (!currentFireball->isEnd)
		{
			currentFireball->render(target);
			fireballs->push(currentFireball);
		}
	}
}
