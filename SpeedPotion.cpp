#include "SpeedPotion.h"

SpeedPotion::SpeedPotion(Player* target, Texture* texture, float x, float y) : Potion(target, texture, x, y)
{
	this->target = target;
	effectTime = 10.f;
	pickedUp = false;
	active = false;
	pos = SPEED_POTION;
	createSprite(texture);
	sprite->setPosition(x, y);
	this->tag = "speed";
}

SpeedPotion::~SpeedPotion()
{
}

void SpeedPotion::deActivate()
{
	target->setVelocity(target->getMinVelocity());
	active = false;
}

void SpeedPotion::setEffect()
{
	target->setVelocity(target->getMinVelocity() * 1.5f);
}

void SpeedPotion::update(const float& dt)
{
	if (target->isCollision(sprite->getGlobalBounds()) && !pickedUp)
	{
		active = true;
		pickedUp = true;
		effectTimer.restart();
		setEffect();
		playSound();
	}
	if (active && target->getVelocity() == target->getMinVelocity())
	{
		setEffect();
	}
	if (effectTimer.getElapsedTime().asSeconds() >= effectTime && active)
	{
		deActivate();
	}
}
