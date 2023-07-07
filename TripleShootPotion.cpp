#include "TripleShootPotion.h"

TripleShootPotion::TripleShootPotion(Player* target, Texture* texture, float x, float y) : Potion(target, texture, x, y)
{
	this->target = target;
	effectTime = 10.f;
	pickedUp = false;
	active = false;
	pos = TRIPLE_SHOOT;
	createSprite(texture);
	sprite->setPosition(x, y);
	this->tag = "triple";
}

TripleShootPotion::~TripleShootPotion()
{

}

void TripleShootPotion::deActivate()
{
	target->removeShootMode(shootModes::triple);
	active = false;
}

void TripleShootPotion::setEffect()
{
	target->setShootMod(shootModes::triple);
}

void TripleShootPotion::update(const float& dt)
{
	if (target->isCollision(sprite->getGlobalBounds()) && !pickedUp)
	{
		active = true;
		pickedUp = true;
		effectTimer.restart();
		setEffect();
		playSound();
	}

	if (active && target->getShootMod() != shootModes::triple && target->getShootMod() != shootModes::doubly_triple)
	{
		setEffect();
	}

	if (effectTimer.getElapsedTime().asSeconds() >= effectTime && active)
	{
		deActivate();
	}
}
