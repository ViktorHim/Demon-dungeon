#include "Animation.h"

Animation::Animation(Texture& textureSheet, IntRect startRect, Sprite& sprite, int rectCount, float animationTimer) :
	textureSheet(textureSheet), sprite(sprite)
{
	this->indexRect = 1;
	this->timer = 0;

	this->animationTimer = animationTimer;

	this->rectCount = rectCount;
	this->startRect = startRect;
	this->currentRect = this->startRect;

	this->width = fabs(this->startRect.width);
	this->sprite.setTexture(this->textureSheet, true);
	this->sprite.setTextureRect(this->startRect);
}

Animation::~Animation()
{

}

void Animation::play(const float& dt)
{
	this->timer += 100.f * dt;	
	if (this->timer >= this->animationTimer)
	{
		this->timer = 0.f;

		if (indexRect != rectCount)
		{
			this->currentRect.left += this->width;
			indexRect++;
		}
		else
		{
			this->currentRect.left = this->startRect.left;
			indexRect = 1;
		}

		this->sprite.setTextureRect(this->currentRect);
	}
}

void Animation::reset()
{
	this->currentRect = this->startRect;
	this->timer = 0.f;
	this->indexRect = 1;
	this->sprite.setTextureRect(this->currentRect);
}