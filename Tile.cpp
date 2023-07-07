#include "Tile.h"



//конструктор
Tile::Tile(int xPos, int yPos, unsigned gridSize, unsigned x, unsigned y, float scale, Texture* texture)
{

	this->pos.width = gridSize;
	this->pos.height = gridSize;
	this->pos.left = xPos;
	this->pos.top = yPos;

	this->scale = scale;

	this->createSprite(texture);

	this->sprite->setPosition(x, y);

	this->animation = nullptr;
	this->tag = "empty";

}

Tile::~Tile()
{

}

bool Tile::isCollision(FloatRect rect)
{
	if (this)
	{
		return this->sprite->getGlobalBounds().intersects(rect);
	}

	return false;
}

//сеттер анимации
void Tile::setAnimation(int rectCount, float animationTimer)
{
	this->animation = new Animation(*this->texture, this->pos, *this->sprite, rectCount, animationTimer);
}

void Tile::setTag(string tag)
{
	this->tag = tag;
}

const FloatRect Tile::getGlobalBounds() const
{
	return this->sprite->getGlobalBounds();
}

const IntRect Tile::getSpriteRect() const
{
	return sprite->getTextureRect();
}

//создание спрайта
void Tile::createSprite(Texture* texture)
{
	this->texture = texture;
	sprite = new Sprite(*texture, pos);
	sprite->setScale(this->scale, this->scale);
}

//обновление
void Tile::update(const float& dt)
{
	if (this)
		this->animation->play(dt);
}

//рендер
void Tile::render(RenderTarget& target)
{
	if(this)
		target.draw(*this->sprite);
}