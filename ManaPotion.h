#pragma once
#include "Potion.h"
#define MANA_BONUS 100
class ManaPotion :
    public Potion
{
private:
public:
	ManaPotion(Player* target, Texture* texture, float x, float y);
	~ManaPotion();

	void setEffect();
};

