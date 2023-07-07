#pragma once
#include "Potion.h"
class TripleShootPotion :
    public Potion
{
private:
public:
	TripleShootPotion(Player* target, Texture* texture, float x, float y);
	~TripleShootPotion();
	void deActivate();
	void setEffect();
	void update(const float& dt);

};

