#include "Summoner.h"

Summoner::Summoner(float x, float y, Texture* texture, IntRect pos, queue<Enemy*>* enemies, float scale) : Enemy(x, y, texture, pos)
{
	initEntityProperty();
	this->pos = pos;
	this->enemies = enemies;

	createSprite(texture);

	setPosition(x, y);
	createAnimationComponent(*texture);
	this->animationComponent->addAnimation("idle", SUMMONER_DEMON_START, 2, 30.f);
	healthBar = new ProgressBar(Vector2f(50, 50), Vector2f(30, 10), nullptr, Color::Red, Color::Black, health, maxHealth);
}


Summoner::~Summoner()
{
}

void Summoner::update(const float& dt, Vector2f targetPos)
{
	healthBar->setPosition(Vector2f(getGlobalBounds().left + getGlobalBounds().width / 2 - 20, getGlobalBounds().top - 15));
	healthBar->setValue(health);
	healthBar->update();

	if (health <= 0.f)
	{
		isAlive = false;
	}

	this->animationComponent->play("idle", dt);
	move(dt, targetPos);
	spawn();
}

void Summoner::initEntityProperty()
{
	this->isAlive = true;
	this->cooldown = 0.1f;
	this->sprite = nullptr;
	this->texture = nullptr;

	this->isReverse = false;
	this->scale = 5.f;
	this->velocity = 120;
	this->maxHealth = 60;
	this->damage = 0;
	health = maxHealth;
	this->time = 10.f;

	this->score = 250;
}

void Summoner::spawn()
{
	if (spawnCooldown.getElapsedTime().asSeconds() >= time)
	{
		spawnCooldown.restart();

		TinyDemon* demon = new TinyDemon(getPosition().x + 100, getPosition().y, texture, TINY_DEMON_START);
		demon->setModificator("weak");
		enemies->push(demon);
		demon = new TinyDemon(getPosition().x - 100, getPosition().y, texture, TINY_DEMON_START);
		demon->setModificator("weak");
		enemies->push(demon); 
		demon = new TinyDemon(getPosition().x, getPosition().y + 100, texture, TINY_DEMON_START);
		demon->setModificator("weak");
		enemies->push(demon);
	}
}
