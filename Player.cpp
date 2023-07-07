#include "Player.h"

// инициализация характеристик игрока из файла
void Player::initEntityProperty(IntRect pos, float scale, PlayerData * data)
{
	this->pos = pos;
	this->scale = scale;
	isReverse = true;
	this->moveDirection.x = 0;
	this->moveDirection.y = 0;


	this->cooldown = data->cooldown;
	this->minVelocity = data->velocity;
	this->velocity = minVelocity;
	this->maxHealth = data->maxHealth;
	this->health = this->maxHealth;
	this->damage = data->damage;
	this->magicResistance = 1;
	this->meleeResistance = 1;
	this->maxMana = data->maxMana;
	this->mana = this->maxMana;

	this->shootMode = shootModes::single;
	this->shootedFirebal = 0;
}

//инициализация компонентов
void Player::initComponents(Texture* texture)
{
	this->createAnimationComponent(*texture);
	this->initAnimations();
}

//инициализация анимаций
void Player::initAnimations()
{
	this->animationComponent->addAnimation("idle", PLAYER_SPRITE_START, 2, 100.f);
	this->animationComponent->addAnimation("walk", PLAYER_SPRITE_START, 2, 25.f);
}

//конструктор
Player::Player(float x, float y, Texture* texture, IntRect pos, PlayerData* data, float scale)
{
	initEntityProperty(pos, scale, data);

	createSprite(texture);

	setPosition(x, y);

	initComponents(this->texture);

	shootComponent = new ShootComponent(0.5f, 600.f, 10.f, FIREBALL, sprite->getTextureRect());
	shootComponent->setCrit(10.f);
}

//деструктор
Player::~Player()
{

}

const float Player::getMana()
{
	return mana;
}

const float Player::getMaxMana()
{
	return maxMana;
}

const float Player::getMinVelocity()
{
	return minVelocity;
}

const int Player::getShootMod()
{
	return shootMode;
}

void Player::setHealth(float health)
{
	if (health > maxHealth)
	{
		this->health = this->maxHealth;
	}
	else
	{
		this->health = health;
	}
}

void Player::setMana(float mana)
{
	if (mana > maxMana)
	{
		this->mana = this->maxMana;
	}
	else
	{
		this->mana = mana;
	}
}

void Player::setShootMod(int mode)
{

	if (this->shootMode == shootModes::doubly && mode == shootModes::triple)
	{
		this->shootMode = shootModes::doubly_triple;
	}
	else if (mode == shootModes::doubly && this->shootMode == shootModes::triple)
	{
		this->shootMode = shootModes::doubly_triple;

	}
	else
	{
		this->shootMode = mode;
	}
}

void Player::setVelocity(float velocity)
{
	this->velocity = velocity;
}

void Player::setSfx(sfxData* data)
{
	this->sfx = data;
	this->shootComponent->setSfx(sfx);

}

void Player::setSettings(Settings* settings)
{
	this->settings = settings;
	this->shootComponent->setSettings(settings);
}


	
		


void Player::removeShootMode(int mode)
{
	if (this->shootMode == shootModes::doubly_triple && mode == shootModes::triple)
	{
		this->shootMode = shootModes::doubly;
	}
	else if (this->shootMode == shootModes::doubly_triple && mode == shootModes::doubly)
	{
		this->shootMode = shootModes::triple;

	}
	else
	{
		this->shootMode = shootModes::single;
	}
}

//const sf::FloatRect Player::getNextPositionBounds(const float& dt) const
//{
//	FloatRect nextPos = this->getGlobalBounds();
//	nextPos.width += this->velocity * dt * this->moveDirection.x;
//	nextPos.height += this->velocity * dt * this->moveDirection.y;
//
//	return nextPos;
//}

//движение игрока
void Player::move(const float& dt, directions d)
{
	float dx, dy; // смещение по осям
	dx = dy = velocity * dt;
	switch (d)
	{
	case directions::up:
	{
		dx *= 0.f;
		dy *= -1.f;
	}
	break;
	case directions::left:
	{
		isReverse = false;

		dx *= -1.f;
		dy *= 0.f;
	}
	break;
	case directions::down:
	{
		dx *= 0.f;
		dy *= 1.f;
	}
	break;
	case directions::right:
	{
		isReverse = true;

		dx *= 1.f;
		dy *= 0.f;
	}
	break;
	default:
		break;
	}

	sprite->move(Vector2f(dx, dy));
}

//стрельба
void Player::shoot()
{

}

//флаг движения
bool Player::isMoving()
{
	if (PRESS_UP || PRESS_DOWN || PRESS_RIGHT || PRESS_LEFT)
	{
		return true;
	}
	return false;
}

//обновление
void Player::update(const float& dt)
{
	this->moveUpdate(dt);
	this->manaUpdate();
	if (this->isMoving())
	{
		this->reverseEntity();
		this->animationComponent->play("walk", dt);
	}
	else
	{
		this->reverseEntity();
		this->animationComponent->play("idle", dt);
	}
}

//обновление движения
void Player::moveUpdate(const float& dt)
{
	if (PRESS_UP)
	{
		move(dt, directions::up);
		moveDirection.y = -1;
	}
	if (PRESS_LEFT)
	{
		move(dt, directions::left);
		moveDirection.x = -1;
	}
	if (PRESS_DOWN)
	{
		move(dt, directions::down);
		moveDirection.y = 1;
	}
	if (PRESS_RIGHT)
	{
		move(dt, directions::right);
		moveDirection.x = 1;
	}
	

}

void Player::shootUpdate(Vector2f* mousePosView, const float& dt)
{
	shootComponent->update(mousePosView, dt);

	if (Mouse::isButtonPressed(Mouse::Left) && mana >= 10)
	{
		if (shootMode == shootModes::triple || shootMode == shootModes::doubly_triple)
		{
			if (shootComponent->addTripleFireball(getCenterPosition(), *mousePosView))
			{
				mana -= 10;
			}
		}
		else
		{
			if (shootComponent->addFireball(getCenterPosition(), *mousePosView))
			{
				mana -= 10;
			}
		}
		
		if (shootMode == shootModes::doubly || shootMode == shootModes::doubly_triple)
		{
			shootedFirebal = 1;
		}
	}

	if (shootMode == shootModes::doubly && shootedFirebal == 1)
	{
		if (shootComponent->addFireball(getCenterPosition(), *mousePosView, 2))
		{
			shootedFirebal = 0;
		}
	}
	else if (shootMode == shootModes::doubly_triple && shootedFirebal == 1)
	{
		if (shootComponent->addTripleFireball(getCenterPosition(), *mousePosView, 2))
		{
			shootedFirebal = 0;
		}
	}
}

void Player::manaUpdate()
{
	if (manaTimer.getElapsedTime().asSeconds() >= 0.08f && mana < maxMana)
	{
		mana++;
		manaTimer.restart();
	}
}

//рендер
void Player::render(RenderTarget* target)
{
	target->draw(*sprite);
	shootComponent->render(target);
}