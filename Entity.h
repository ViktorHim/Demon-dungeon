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


enum directions // ����������� ��������
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
	virtual void initEntityProperty();//������������� �������������
protected:
	sfxData* sfx;
	Settings* settings;

	//������� ��� ��������
	Sprite* sprite; // ������
	Texture* texture;// �������� 
	IntRect pos;//������������� �������������� ��������

	AnimationComponent* animationComponent;

	//���������� �������������� ��������
	Clock cooldownClock;
	float cooldown;

	float health; // ��������
	float maxHealth;
	float damage; // ��������� ����

	// ����������� �������
	bool isReverse;
	// ������� �������
	float scale;
	int score;
public:
	float velocity; // �������� ������������
	bool isAlive;

	// ����������� // ����������
	Entity();
	virtual ~Entity();
	//���������
	bool isCollision(FloatRect rect);
	// �������
	virtual void setPosition(const float x, const float y);// ��������� �������
	virtual void setDamage(float damage);
	void setSfx(sfxData* data);
	void setSettings(Settings* settings);
	// ������� 
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
	// �������
	void createSprite(Texture* texture);
	void createAnimationComponent(Texture& texture);


	void reverseEntity();//�������� ��������

	void playSound(); //

	//������
	virtual void render(RenderTarget* target = nullptr);
};