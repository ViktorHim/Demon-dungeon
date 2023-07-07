#include "ManaPotion.h"

ManaPotion::ManaPotion(Player* target, Texture* texture, float x, float y) : Potion(target, texture, x, y)
{
	this->target = target;
	effectTime = 0.f;
	pickedUp = false;
	active = false;
	pos = MANA_POTION;
	createSprite(texture);
	sprite->setPosition(x, y);
	this->tag = "mana";
}

ManaPotion::~ManaPotion()
{
}

void ManaPotion::setEffect()
{
	if (target->getMana() + MANA_BONUS < target->getMaxMana())
	{
		target->setMana(target->getMana() + MANA_BONUS);
	}
	else
	{
		target->setMana(target->getMaxMana());
	}
}
