#pragma once

#include <iostream>
#include <map>
#include <cmath>

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"
#include "SFML/System.hpp"

using namespace std;
using namespace sf;

class Animation
{
public:
	Sprite& sprite;
	Texture& textureSheet;

	IntRect startRect;
	IntRect currentRect;

	int rectCount;
	int indexRect;
	int width;

	float animationTimer;
	float timer;

	Animation(Texture& textureSheet, IntRect startRect, Sprite& sprite, int rectCount, float animationTimer);
	~Animation();

	void play(const float& dt);
	void reset();
};