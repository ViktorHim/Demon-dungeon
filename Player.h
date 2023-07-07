#pragma once
#include "Entity.h"
#include "DataPaths.h"
#include "ShootComponent.h"
#include "Data.h"

#define PRESS_UP Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up)
#define PRESS_LEFT Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left)
#define PRESS_DOWN Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::Down)
#define PRESS_RIGHT Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right)

#define PLAYER_SPRITE_START IntRect(128, 172, 16, 19)
#define PLAYER_SPRITE_WALK IntRect(160, 172, 16, 19)

enum shootModes
{
	single,
	doubly,
	triple,
	doubly_triple
};

class Player :
    public Entity
{
private:
	//инициализация

	void initEntityProperty(IntRect pos, float scale, PlayerData * data);
	void initComponents(Texture* texture);
	void initAnimations();
	//физичесике характеристики
	float minVelocity;
	int meleeResistance;
	int magicResistance;
	float maxMana;
	float mana;
	Clock manaTimer;

	Vector2i moveDirection;

	int shootMode;
	int shootedFirebal;
public:
	ShootComponent* shootComponent;

	//конструктор / деструктор
	Player(float x, float y, Texture* texture, IntRect pos, PlayerData* data ,float scale = 5.f);
	virtual ~Player();
	
	const float getMana();
	const float getMaxMana();
	const float getMinVelocity();
	const int getShootMod();

	void setHealth(float health);
	void setMana(float mana);
	void setShootMod(int mode);
	void setVelocity(float velocity);
	void setSfx(sfxData* data);
	void setSettings(Settings* settings);

	void removeShootMode(int mode);

	//функции
	void move(const float& dt, directions d);
	void shoot();

	bool isMoving();

	//обновление
	void update(const float& dt);
	void moveUpdate(const float& dt);
	void shootUpdate(Vector2f * mousePosView, const float& dt);
	void manaUpdate();

	//рендер
	void render(RenderTarget* target = nullptr);
};