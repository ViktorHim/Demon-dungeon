#include "Wizzard.h"

Wizzard::Wizzard(float x, float y, Texture* texture, IntRect pos, float scale) : Enemy(x, y, texture, pos)
{
	initEntityProperty();
	this->pos = pos;

	createSprite(texture);

	setPosition(x, y);
	createAnimationComponent(*texture);
	this->animationComponent->addAnimation("idle",WIZZARD_START, 2, 30.f);
	healthBar = new ProgressBar(Vector2f(50, 50), Vector2f(30, 10), nullptr, Color::Red, Color::Black, health, maxHealth);
	shootComponent = new ShootComponent(1.f, 400.f, 10.f, FIREBALL, sprite->getTextureRect());
}

Wizzard::~Wizzard()
{
	delete shootComponent;
}

void Wizzard::setSfx(sfxData* data)
{
	this->sfx = data;
	this->shootComponent->setSfx(sfx);
}

void Wizzard::setSettings(Settings* settings)
{
	this->settings = settings;
	this->shootComponent->setSettings(settings);
}



void Wizzard::update(const float& dt, Vector2f targetPos)
{
	healthBar->setPosition(Vector2f(getGlobalBounds().left + getGlobalBounds().width / 2 - 15, getGlobalBounds().top - 15));
	healthBar->setValue(health);
	healthBar->update();
	if (health <= 0.f)
	{
		isAlive = false;
	}

	this->animationComponent->play("idle", dt);

	shootComponent->addFireball(getCenterPosition(), targetPos);
	shootComponent->update(&targetPos, dt);
	
	move(dt, targetPos);
}

void Wizzard::move(const float& dt, Vector2f targetPos)
{
	Vector2f pos;
	if (follow)
	{
		pos = targetPos;
	}
	else
	{
		pos = this->targetPos;
	}

	direction.x = pos.x - getPosition().x;
	direction.y = pos.y - getPosition().y;
	length = sqrt(direction.x * direction.x + direction.y * direction.y);

	if (length < 300)
	{
		dx =- dt * velocity * direction.x / length;
		dy =- dt * velocity * direction.y / length;
	}
	else if(length > 500)
	{
		dx = dt * velocity * direction.x / length;
		dy = dt * velocity * direction.y / length;
	}
	else
	{
		follow = true;
	}
	
	sprite->move(Vector2f(dx, dy));
	

	if (dx > 0)
	{
		isReverse = true;
	}
	else
	{
		isReverse = false;
	}
	reverseEntity();


}

void Wizzard::render(RenderTarget* target)
{
	if (this->sprite && isAlive)
	{
		target->draw(*sprite);
		healthBar->render(target);
	}

	this->shootComponent->render(target);
}

void Wizzard::initEntityProperty()
{
	this->isAlive = true;
	this->cooldown = 0.1f;
	this->sprite = nullptr;
	this->texture = nullptr;
	this->velocityMultiplier = 1.4f;

	this->isReverse = false;
	this->scale = 5.f;
	this->velocity = 200;
	this->maxHealth = 40;
	this->damage = 0;
	health = maxHealth;

	this->score = 150;
}

void Wizzard::setModificator(string key)
{
	if (key == "dark")
	{
		this->velocity *= this->velocityMultiplier;
		this->score *= 2;
		shootComponent->setCrit(10.f);
		shootComponent->setDamage(20.f);
		this->sprite->setColor(Color(24, 24, 38, 255));
	}
	else if (key == "founder")
	{
		this->velocity *= this->velocityMultiplier;
		this->score *= 2;
		shootComponent->setCrit(50.f);
		shootComponent->setDamage(30.f);
		this->sprite->setColor(Color(64, 40, 63, 255));
	}
	
}
