#include "Entity.h"

//инициализация характеристик
void Entity::initEntityProperty()
{
	this->settings = nullptr;
	this->sfx = nullptr;
	this->cooldown = 1;
	this->sprite = nullptr;
	this->texture = nullptr;

	this->isReverse = false;
	this->scale = 5.f;
	this->velocity = 100;
	this->maxHealth = 500;
	this->damage = 300;
	health = maxHealth;
	this->score = 50;
	this->isAlive = true;
}

//конструктор
Entity::Entity()
{
	initEntityProperty();
}

//деструктор
Entity::~Entity()
{
	delete this->sprite;
	delete this->animationComponent;
}

bool Entity::isCollision(FloatRect  rect)
{
	if (this->sprite)
	{
		return this->sprite->getGlobalBounds().intersects(rect);
	}
	return false;
}

//создание спрайта
void Entity::createSprite(Texture* texture)
{
	this->texture = texture;
	this->sprite = new Sprite(*texture, pos);
	this->sprite->setScale(scale, scale);
}

//создание компонента анимации
void Entity::createAnimationComponent(Texture& texture)
{
	this->animationComponent = new AnimationComponent(*this->sprite, texture);
}

//сеттеры
void Entity::setPosition(const float x, const float y)//установка позиции
{
	if (sprite)
	{
		this->sprite->setPosition(x, y);
	}
}

void Entity::setDamage(float damage)
{
	if (cooldownClock.getElapsedTime().asSeconds() >= cooldown)
	{
		playSound();

		if (damage >= health)
		{
			health = 0.f;
		}
		else
		{
			health -= damage;
		}
		cooldownClock.restart();
		if (health <= 0)
		{
			isAlive = false;
		}
	}
}

void Entity::setSfx(sfxData* data)
{
	this->sfx = data;
}

void Entity::setSettings(Settings* settings)
{
	this->settings = settings;
}


const Vector2f& Entity::getPosition() const //получение позиции
{
	return this->sprite->getPosition();
}

const Vector2f& Entity::getCenterPosition() const
{
	Vector2f pos = sprite->getPosition();
	Vector2f size = Vector2f(sprite->getGlobalBounds().width, sprite->getGlobalBounds().height);
	return Vector2f(pos.x + size.x / 2, pos.y + size.y / 2);
}

const Vector2i& Entity::getGridPosition(const int gridSize) const
{
	return Vector2i(
		static_cast<int>(this->sprite->getPosition().x) / gridSize,
		static_cast<int>(this->sprite->getPosition().y) / gridSize
	);
}

const FloatRect Entity::getGlobalBounds() const
{
	return this->sprite->getGlobalBounds();
}

void Entity::setInstanceDamage(float damage)
{
	playSound();

	if (damage >= health)
	{
		health = 0.f;
	}
	else
	{
		health -= damage;
	}

	if (health <= 0)
	{
		isAlive = false;
	}
}

int Entity::getScore()
{
	return score;
}

//const sf::FloatRect Entity::getNextPositionBounds(const float& dt) const
//{
//	return sf::FloatRect();
//}

const float Entity::getDamage() const
{
	return this->damage;
}

const float Entity::getHealth() const
{
	return health;
}

const float Entity::getMaxHealth() const
{
	return maxHealth;
}

const float Entity::getVelocity() const
{
	return velocity;
}


//разворот сущности
void Entity::reverseEntity()
{
	if (this->isReverse)
	{
		this->sprite->setOrigin(0.f, 0.f);

		this->sprite->setScale(this->scale, this->scale);
	}
	else
	{
		this->sprite->setOrigin(this->pos.width, 0.f);

		this->sprite->setScale(-this->scale, this->scale);
	}
}

void Entity::playSound()
{
	if (sfx && settings && settings->sfx)
	{
		sfx->sounds[sounds::damage].play();
	}
}

//рендер
void Entity::render(RenderTarget* target)
{
	if (sprite)
	{
		target->draw(*sprite);
	}
}