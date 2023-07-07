#include "Potion.h"

Potion::Potion(Player* target, Texture* texture, float x, float y)
{
	this->sfx = nullptr;
	this->settings = nullptr;
	this->target = target;
	effectTime = 5.f;
	pickedUp = false;
	active = false;
	pos = HEALTH_POTION;
	createSprite(texture);
	sprite->setPosition(x,y);
}

Potion::~Potion()
{
	delete sprite;
}

void Potion::createSprite(Texture* texture)
{
	this->texture = texture;
	this->sprite = new Sprite(*texture, pos);
	this->sprite->setScale(3,3);
}

bool Potion::isPickedUp()
{
	return pickedUp;
}

bool Potion::isActive()
{
	return active;
}

string Potion::getTag()
{
	return tag;
}

float Potion::getRemainingTime()
{
	float remainTime = effectTime - effectTimer.getElapsedTime().asSeconds();
	return   remainTime  > 0 && active ? remainTime : 0;
}

void Potion::deActivate()
{
	active = false;
}

void Potion::setSfx(sfxData* data)
{
	this->sfx = data;
}

void Potion::setSettings(Settings* settings)
{
	this->settings = settings;
}

void Potion::playSound()
{
	if (sfx && settings && settings->sfx)
	{
		sfx->sounds[sounds::potion].play();
	}
}

void Potion::update(const float& dt)
{
	if (target->isCollision(sprite->getGlobalBounds()) && !pickedUp)
	{
		active = true;
		pickedUp = true;
		effectTimer.restart();
		setEffect();
		playSound();
	}

	if (effectTimer.getElapsedTime().asSeconds() >= effectTime && active)
	{
		deActivate();
	}
}

void Potion::render(RenderTarget* target)
{
	if (sprite && !pickedUp)
	{
		target->draw(*sprite);
	}
}
