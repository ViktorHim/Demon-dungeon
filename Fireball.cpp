#include "Fireball.h"

Fireball::Fireball(Vector2f playerPos, Vector2f mousePos, float damage, Texture* texture, IntRect pos, IntRect playerSize, float velocity)
{
	this->damage = damage;
	this->pos = pos;
	this->createSprite(texture);
	sprite->setPosition(playerPos);

	direction.x = mousePos.x - playerPos.x;
	direction.y = mousePos.y - playerPos.y;
	rotation = -(atan2(direction.x, direction.y) * 180 / PI - 90);
	length = sqrt(direction.x * direction.x + direction.y * direction.y);
	sprite->setRotation(rotation);
	this->velocity = velocity;
	isEnd = false;
	lifeTime = 2.5f;
}

Fireball::~Fireball()
{

}

const Vector2f& Fireball::getPosition() const
{
	return this->sprite->getPosition();
}

const Vector2i& Fireball::getGridPosition(const int gridSize) const
{
	return Vector2i(
		static_cast<int>(this->sprite->getPosition().x) / gridSize,
		static_cast<int>(this->sprite->getPosition().y) / gridSize
	);
}

 FloatRect *  Fireball::getGlobalBounds()
{
	return new FloatRect(this->sprite->getGlobalBounds());
}

 bool Fireball::isCollision(FloatRect rect)
 {
	 if (this->sprite)
	 {
		 return this->sprite->getGlobalBounds().intersects(rect);
	 }
	 return false;
 }

void Fireball::update(const float& dt)
{
	if (lifeTimeClock.getElapsedTime().asSeconds() < lifeTime)
	{
		float dx = dt * velocity * direction.x / length;
		float dy = dt * velocity * direction.y / length;

		sprite->move(Vector2f(dx, dy));
	}
	else
	{
		isEnd = true;
	}
	
}

void Fireball::setColor(Color color)
{
	sprite->setColor(color);
}

float Fireball::getDamage()
{
	return damage;
}

void Fireball::createSprite(Texture* texture)
{
	this->texture = texture;
	this->sprite = new Sprite(*texture, pos);
	this->sprite->setScale(5.f, 5.f);
}

void Fireball::render(RenderTarget* target)
{
	if (!isEnd)
	{
		target->draw(*sprite);
	}
}
