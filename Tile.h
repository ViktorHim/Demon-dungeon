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
	Sprite* sprite; // спрайт
	Texture* texture;// текстура 
	IntRect pos;//прямоугольник ограничивающий текстуру
	Animation* animation; // анимация тайла

	float scale; //масштаб тайла

	string tag;
protected:
	
public:
	//конструктор / деструктор
	Tile(int xPos, int yPos, unsigned gridSize, unsigned x, unsigned y, float scale, Texture* texture);
	virtual ~Tile();

	bool isCollision(FloatRect rect);
	//сеттеры
	void setAnimation(int rectCount, float animationTimer);
	void setTag(string tag);
	//геттеры
	const FloatRect getGlobalBounds() const;
	const IntRect getSpriteRect() const;
	//функции
	void createSprite(Texture* texture);

	//обновление
	void update(const float& dt);
	
	//рендер
	void render(RenderTarget& target);
};