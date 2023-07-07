#pragma once
#include "Potion.h"
class SpeedPotion :
    public Potion
{
private:
public:
	SpeedPotion(Player* target, Texture* texture, float x, float y);
	~SpeedPotion();
	void deActivate();
	void setEffect();
	void update(const float& dt);

};

