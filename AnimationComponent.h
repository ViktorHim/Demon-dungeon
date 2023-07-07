#pragma once
#include "Animation.h"

class AnimationComponent
{
private:
	map <string, Animation*> animations;
	Animation* lastAnimation;

	Sprite& sprite;
	Texture& textureSheet;
public:
	AnimationComponent(Sprite& sprite, Texture& textureSheet);
	virtual ~AnimationComponent();

	Animation* getAnimation(string key);

	void addAnimation(const string key, IntRect startRect, int rectCount, float animationTimer);

	void play(const string key, const float& dt);
};