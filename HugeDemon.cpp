#include "HugeDemon.h"

HugeDemon::HugeDemon(float x, float y, Texture* texture, IntRect pos, float scale) :  Enemy(x, y, texture, pos)
{
	initEntityProperty();
	this->pos = pos;

	createSprite(texture);
	
	setPosition(x, y);
	createAnimationComponent(*texture);
	this->animationComponent->addAnimation("idle", HUGE_DEMON_START, 2, 100.f);

	healthBar = new ProgressBar(Vector2f(50, 50), Vector2f(70, 10), nullptr, Color::Red, Color::Black, health, maxHealth);
}

HugeDemon::~HugeDemon()
{

}

void HugeDemon::initEntityProperty()
{
	this->isAlive = true;
	this->cooldown = 0.1f;
	this->sprite = nullptr;
	this->texture = nullptr;

	this->isReverse = false;
	this->scale = 4.f;
	this->velocity = 100;
	this->maxHealth = 100;
	this->damage = 10;
	health = maxHealth;

	this->score = 200;

	this->velocityMultiplier = 1.4f;
	this->healthMultiplier = 0.8f;
	this->damageMultiplier = 2.f;
}
void HugeDemon::update(const float& dt, Vector2f targetPos)
{
	healthBar->setPosition(Vector2f(getGlobalBounds().left + getGlobalBounds().width / 2 - 32, getGlobalBounds().top - 20));
	healthBar->setValue(health);
	healthBar->update();


	this->animationComponent->play("idle", dt);
	move(dt, targetPos);
}

void HugeDemon::setModificator(string key)
{
	if (key == "stronger")
	{
		this->velocity *= velocityMultiplier;
		this->maxHealth *= healthMultiplier;
		this->health = maxHealth;
		this->damage *= damageMultiplier;
		this->score *= 2;

	}
	else if(key == "srtrongest")
	{
		this->velocityMultiplier = 1.6f;
		this->healthMultiplier = 0.6f;
		this->damageMultiplier = 3.5f;
		this->velocity *= velocityMultiplier;
		this->maxHealth *= healthMultiplier;
		this->health = maxHealth;
		this->damage *= damageMultiplier;
		this->score *= 4;
	}

	
	this->scale = 4.5f;
	this->sprite->setScale(Vector2f(4.5f, 4.5f));
	this->sprite->setColor(Color(34, 38, 35, 255));
	healthBar = new ProgressBar(Vector2f(50, 50), Vector2f(70, 10), nullptr, Color::Red, Color::Black, health, maxHealth);
}


