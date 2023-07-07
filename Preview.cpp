#include "Preview.h"

Preview::Preview(RenderWindow* window, Font* font) : BasicWindow(window, font)
{
	this->window = window;
	background.setSize(Vector2f(this->window->getSize().x, this->window->getSize().y));
	background.setFillColor(Color(20, 20, 20, 255));
	this->font = font;

	menuText.setFont(*font);
	menuText.setCharacterSize(40);
	menuText.setString("Виктор Химлих О722Б");
	menuText.setPosition(this->window->getSize().x / 2 - menuText.getGlobalBounds().width / 2, this->window->getSize().y / 2 - menuText.getGlobalBounds().height / 2);

	animationTime = 5.f;
	endScale = 2.5f;
	isEnd = false;
}

Preview::~Preview()
{
}

void Preview::update()
{
	menuText.setPosition(this->window->getSize().x / 2 - menuText.getGlobalBounds().width / 2, this->window->getSize().y / 2 - menuText.getGlobalBounds().height / 2);
	Vector2f currentScale = menuText.getScale();

	if (currentScale.x < endScale)
	{
		currentScale.x += 0.01;
		currentScale.y += 0.01;
		menuText.setScale(currentScale);
	}
	else
	{
		isEnd = true;
	}
}

bool Preview::getIsEnd()
{
	return isEnd;
}

void Preview::render(RenderTarget* target)
{
	target->draw(background);
	target->draw(menuText);
}

