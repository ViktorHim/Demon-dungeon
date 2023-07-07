#include "TinyDemon.h"

TinyDemon::TinyDemon(float x, float y, Texture* texture, IntRect pos, float scale) : Enemy(x,y,texture, pos)
{
	initEntityProperty();
	this->pos = pos;


	createSprite(texture);


	setPosition(x, y);
	createAnimationComponent(*texture);
	this->animationComponent->addAnimation("idle", TINY_DEMON_START, 2, 30.f);
	healthBar = new ProgressBar(Vector2f(50, 50), Vector2f(30, 10), nullptr, Color::Red, Color::Black, health, maxHealth);
}

TinyDemon::~TinyDemon()
{
	
}

void TinyDemon::update(const float& dt, Vector2f targetPos)
{
	healthBar->setPosition(Vector2f(getGlobalBounds().left + getGlobalBounds().width / 2 - 15, getGlobalBounds().top - 15));
	healthBar->setValue(health);
	healthBar->update();


	this->animationComponent->play("idle", dt);
	move(dt, targetPos);
}



void TinyDemon::initEntityProperty()
{
	this->isAlive = true;
	this->cooldown = 0.1f;
	this->sprite = nullptr;
	this->texture = nullptr;
	this->velocityMultiplier = 1.4f;

	this->isReverse = false;
	this->scale = 5.f;
	this->velocity = 180 + rand() % 50;
	this->maxHealth = 20;
	this->damage = 2;
	health = maxHealth;

	this->score = 50;
}

void TinyDemon::setModificator(string key)
{
	if (key == "fast")
	{
		this->velocity *= this->velocityMultiplier;
		this->sprite->setScale(Vector2f(4.f, 4.f));
		this->scale = 4.f;
		this->score *= 2;
		this->sprite->setColor(Color(23, 189, 42, 255));
	}
	else if(key == "faster")
	{
		this->velocityMultiplier = 1.8f;
		this->velocity *= this->velocityMultiplier;
		this->sprite->setScale(Vector2f(3.8f, 3.8f));
		this->scale = 3.8f;
		this->score *= 4;
		this->sprite->setColor(Color(23, 189, 42, 255));
	}
	else if(key == "weak")
	{
		this->score = 10;
		this->maxHealth = 10;
		this->health = maxHealth;
		healthBar = new ProgressBar(Vector2f(50, 50), Vector2f(30, 10), nullptr, Color::Red, Color::Black, health, maxHealth);
		this->sprite->setColor(Color(168, 10, 252, 255));
	}
	
}



