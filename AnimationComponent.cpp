#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(Sprite& sprite, Texture& textureSheet)
	:sprite(sprite), textureSheet(textureSheet)
{
	this->lastAnimation = nullptr;
}

AnimationComponent::~AnimationComponent()
{
	for (auto& i : this->animations)
	{
		delete i.second;
	}
}

Animation* AnimationComponent::getAnimation(string key)
{
	return this->animations[key];
}

void AnimationComponent::addAnimation(const string key , IntRect startRect , int rectCount, float animationTimer)
{
	this->animations[key] = new Animation(this->textureSheet, startRect, this->sprite, rectCount, animationTimer);
}

void AnimationComponent::play(const string key, const float& dt)
{
	if (this->lastAnimation != this->animations[key])
	{
		if (this->lastAnimation != nullptr)
		{
			this->lastAnimation->reset();
		}
		this->lastAnimation = this->animations[key];

	}
	animations[key]->play(dt);
}