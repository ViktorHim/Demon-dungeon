#pragma once
#include "Potion.h"
#define HP_BONUS 50
class HealthPotion : public Potion
{
private:
public:
	HealthPotion(Player* target, Texture* texture, float x, float y);
	~HealthPotion();

	void setEffect();
};

