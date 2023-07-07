#include "Demon.h"

Demon::Demon(float x, float y, Texture* texture, IntRect pos, float scale) : Enemy(x, y, texture, pos)
{
	initEntityProperty();
	this->pos = pos;


	createSprite(texture);

	setPosition(x, y);
	createAnimationComponent(*texture);
	this->animationComponent->addAnimation("idle", DEMON_START, 2, 30.f);
	healthBar = new ProgressBar(Vector2f(50, 50), Vector2f(30, 10), nullptr, Color::Red, Color::Black, health, maxHealth);
}

Demon::~Demon()
{
	
}

void Demon::update(const float& dt, Vector2f targetPos)
{
	healthBar->setPosition(Vector2f(getGlobalBounds().left + getGlobalBounds().width / 2 - 20, getGlobalBounds().top - 15));
	healthBar->setValue(health);
	healthBar->update();


	this->animationComponent->play("idle", dt);
	move(dt, targetPos);
}


void Demon::initEntityProperty()
{
	this->isAlive = true;
	this->cooldown = 0.1f;
	this->sprite = nullptr;
	this->texture = nullptr;

	this->isReverse = false;
	this->scale = 5.f;
	this->velocity = 150;
	this->maxHealth = 40;
	this->damage = 5;
	health = maxHealth;

	this->score = 100;

	this->velocityMultiplier = 1.3f;
	this->damageMultiplier = 1.5f;
}

void Demon::setModificator(string key)
{
	if (key == "stronger")
	{
		this->velocity *= velocityMultiplier;
		this->damage *= damageMultiplier;
		this->score *= 2;

	}
	else if(key == "strongest")
	{
		this->velocityMultiplier = 1.6f;
		this->damageMultiplier = 2.5f;
		this->velocity *= velocityMultiplier;
		this->damage *= damageMultiplier;
		this->score *= 4;

	}
	
	this->sprite->setColor(Color(161, 212, 21, 255));
}

