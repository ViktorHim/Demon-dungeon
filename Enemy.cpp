#include "Enemy.h"




Enemy::Enemy(float x, float y, Texture* texture, IntRect pos, float scale)
{
	
	initEntityProperty();
	this->pos = pos;
	this->targetPos;
	this->follow = true;
	this->dx = 0.f;
	this->dy = 0.f;
	createSprite(texture);

	setPosition(x, y);
	createAnimationComponent(*texture);

	this->animationComponent->addAnimation("idle", DEMON_START, 2, 100.f);
	healthBar = new ProgressBar(Vector2f(50, 50), Vector2f(30, 10), nullptr, Color::Red, Color::Black, health, maxHealth);
	healthBar->setPosition(Vector2f(x, y - 10));

}

Enemy::~Enemy()
{
	
}

void Enemy::initEntityProperty()
{
	this->isAlive = true;
	this->cooldown = 0.3f;
	this->sprite = nullptr;
	this->texture = nullptr;

	this->isReverse = false;
	this->scale = 5.f;

	this->velocity = 100;
	this->maxHealth = 40;
	this->damage = 300;
	health = maxHealth;

	this->score = 100;
}

void Enemy::setTarget(Vector2f targetPos)
{
	this->targetPos = targetPos;
}

bool Enemy::getFollow()
{
	return follow;
}

Vector2i Enemy::getVelocity()
{
	int x, y;
	
	x = dx >= 0 ? 1 : -1;
	y = dy >= 0 ? 1 : -1;

	
	return Vector2i(x,y);
}

void Enemy::setFollow(bool follow)
{
	this->follow = follow;
}





void Enemy::update(const float& dt, Vector2f targetPos)
{
	healthBar->setPosition(Vector2f(getGlobalBounds().left, getGlobalBounds().top - 10));
	healthBar->setValue(health);
	healthBar->update();

	this->animationComponent->play("idle", dt);
	move(dt, targetPos);
}

void Enemy::move(const float& dt,Vector2f targetPos)
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

	 dx =dt * velocity * direction.x / length;
	 dy =dt * velocity * direction.y / length;

	if (dx > 0)
	{
		isReverse = true;
	}
	else
	{
		isReverse = false;
	}
	reverseEntity();

	if (length > 5)
	{
		sprite->move(Vector2f(dx, dy));
	}
	else
	{
		follow = true;
	}
}



void Enemy::render(RenderTarget* target)
{

	if (this->sprite && isAlive)
	{
		target->draw(*sprite);
		healthBar->render(target);
	}
}
