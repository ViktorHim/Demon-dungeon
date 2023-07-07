#include "HealthPotion.h"

HealthPotion::HealthPotion(Player* target, Texture* texture, float x, float y) : Potion(target, texture, x, y)
{
	effectTime = 0.f;
	this->tag = "health";
}

HealthPotion::~HealthPotion()
{
}

void HealthPotion::setEffect()
{
	
	if (target->getHealth() + HP_BONUS < target->getMaxHealth())
	{
		target->setHealth(target->getHealth() + HP_BONUS);
	}
	else
	{
		target->setHealth(target->getMaxHealth());
	}
}


