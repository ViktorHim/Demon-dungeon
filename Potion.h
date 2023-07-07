#pragma once
#include "Player.h"

#define HEALTH_POTION IntRect(291, 339,10, 10)
#define MANA_POTION IntRect(307, 339,10, 10)
#define TRIPLE_SHOOT IntRect(339, 339,10, 10)
#define SPEED_POTION IntRect(323, 339,10, 10)
#define DOUBLE_SHOOT IntRect(340, 355,7, 10)

class Potion
{
private:
protected:
	sfxData* sfx;
	Settings* settings;

	Player* target;

	Sprite* sprite; // спрайт
	Texture* texture;// текстура 
	IntRect pos;//прямоугольник ограничивающий текстуру

	bool pickedUp;
	bool active;
	string tag;

	Clock effectTimer;
	float effectTime;
public:
	Potion(Player* target, Texture * texture, float x, float y);
	virtual ~Potion();

	void createSprite(Texture* texture);
	bool isPickedUp();
	bool isActive();

	string getTag();
	float getRemainingTime();

	virtual void setEffect() = 0;
	virtual void deActivate();

	void setSfx(sfxData* data);
	void setSettings(Settings* settings);

	void playSound();
	//обновление
	virtual void update(const float& dt);
	//рендер
	void render(RenderTarget* target = nullptr);
};

