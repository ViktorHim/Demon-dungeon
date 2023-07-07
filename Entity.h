#pragma once

#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <cmath>
#include <fstream>


#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"
#include "SFML/System.hpp"
#include "DataPaths.h"
#include "Data.h"

using namespace std;
using namespace sf;

#include "AnimationComponent.h"


enum directions // направления движения
{
	up,
	left,
	down,
	right,
	upLeft,
	upRight,
	downLeft,
	downRight
};


class Entity
{
private:
	virtual void initEntityProperty();//инициализация характеристик
protected:
	sfxData* sfx;
	Settings* settings;

	//внешний вид сущности
	Sprite* sprite; // спрайт
	Texture* texture;// текстура 
	IntRect pos;//прямоугольник ограничивающий текстуру

	AnimationComponent* animationComponent;

	//физичесике характеристики сущности
	Clock cooldownClock;
	float cooldown;

	float health; // здоровье
	float maxHealth;
	float damage; // наносимый урон

	// направление спрайта
	bool isReverse;
	// масштаб спрайта
	float scale;
	int score;
public:
	float velocity; // скорость передвижения
	bool isAlive;

	// конструктор // деструктор
	Entity();
	virtual ~Entity();
	//состояния
	bool isCollision(FloatRect rect);
	// сеттеры
	virtual void setPosition(const float x, const float y);// установка позиции
	virtual void setDamage(float damage);
	void setSfx(sfxData* data);
	void setSettings(Settings* settings);
	// геттеры 
	virtual const Vector2f& getPosition() const;
	virtual const Vector2f& getCenterPosition() const;
	virtual const Vector2i& getGridPosition(const int gridSize) const;
	virtual const FloatRect getGlobalBounds() const;
	void setInstanceDamage(float damage);
	int getScore();
	virtual const float getDamage() const;
	const float getHealth() const;
	const float getMaxHealth() const;
	const float getVelocity() const;
	// функции
	void createSprite(Texture* texture);
	void createAnimationComponent(Texture& texture);


	void reverseEntity();//разворот сущности

	void playSound(); //

	//рендер
	virtual void render(RenderTarget* target = nullptr);
};