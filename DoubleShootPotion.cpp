#include "DoubleShootPotion.h"

DoubleShootPotion::DoubleShootPotion(Player* target, Texture* texture, float x, float y) : Potion(target, texture, x, y)
{
	this->target = target;
	effectTime = 10.f;
	pickedUp = false;
	active = false;
	pos = DOUBLE_SHOOT;
	createSprite(texture);
	sprite->setPosition(x, y);
	this->tag = "double";
}

DoubleShootPotion::~DoubleShootPotion()
{
}

void DoubleShootPotion::deActivate()
{
	target->removeShootMode(shootModes::doubly);
	active = false;
}

void DoubleShootPotion::setEffect()
{
	target->setShootMod(shootModes::doubly);
}

void DoubleShootPotion::update(const float& dt)
{
	if (target->isCollision(sprite->getGlobalBounds()) && !pickedUp)
	{
		active = true;
		pickedUp = true;
		effectTimer.restart();
		setEffect();
		playSound();
	}
	if (active && target->getShootMod() != shootModes::doubly && target->getShootMod() != shootModes::doubly_triple)
	{
		setEffect();
	}

	if (effectTimer.getElapsedTime().asSeconds() >= effectTime && active)
	{
		deActivate();
	}
}
