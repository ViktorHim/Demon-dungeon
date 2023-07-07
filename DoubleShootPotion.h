#pragma once
#include "Potion.h"
class DoubleShootPotion :
    public Potion
{
private:
public:
	DoubleShootPotion(Player* target, Texture* texture, float x, float y);
	~DoubleShootPotion();
	void deActivate();
	void setEffect();
	void update(const float& dt);
};

