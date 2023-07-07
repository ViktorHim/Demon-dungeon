#include "PauseMenu.h"


PauseMenu::PauseMenu(RenderWindow* window, Font* font) : BasicWindow(window, font)
{
	this->window = window;
	background.setSize(Vector2f(this->window->getSize().x, this->window->getSize().y));
	background.setFillColor(Color(20, 20, 20, 200));
	this->font = font;

	menuText.setFont(*font);
	menuText.setCharacterSize(40);
	menuText.setString("Пауза");
	menuText.setPosition(this->window->getSize().x / 2 - menuText.getGlobalBounds().width / 2, 100);
}

PauseMenu::~PauseMenu()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

void PauseMenu::setPosition(Vector2f pos)
{
	float centerX = (window->getSize().x - buttons["quit"]->getSize().x) / 2.f;
	menuText.setPosition(pos.x + this->window->getSize().x / 2 - menuText.getGlobalBounds().width / 2, pos.y +  100);
	this->buttons["resume"]->setPosition(Vector2f(pos.x + centerX, pos.y + 300.f));
	this->buttons["quit"]->setPosition(Vector2f(pos.x + centerX, pos.y + 450.f));
	this->background.setPosition(pos);
}