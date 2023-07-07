#pragma once
#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <vector>
#include <cmath>

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"
#include "SFML/System.hpp"

using namespace std;
using namespace sf;

#include "AnimationComponent.h"
class Tile
{
private:
	Sprite* sprite; // ������
	Texture* texture;// �������� 
	IntRect pos;//������������� �������������� ��������
	Animation* animation; // �������� �����

	float scale; //������� �����

	string tag;
protected:
	
public:
	//����������� / ����������
	Tile(int xPos, int yPos, unsigned gridSize, unsigned x, unsigned y, float scale, Texture* texture);
	virtual ~Tile();

	bool isCollision(FloatRect rect);
	//�������
	void setAnimation(int rectCount, float animationTimer);
	void setTag(string tag);
	//�������
	const FloatRect getGlobalBounds() const;
	const IntRect getSpriteRect() const;
	//�������
	void createSprite(Texture* texture);

	//����������
	void update(const float& dt);
	
	//������
	void render(RenderTarget& target);
};