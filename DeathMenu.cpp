#include "DeathMenu.h"

DeathMenu::DeathMenu(RenderWindow* window, Font* font) : BasicWindow(window, font)
{
	this->window = window;
	background.setSize(Vector2f(this->window->getSize().x, this->window->getSize().y));
	background.setFillColor(Color(20, 20, 20, 200));
	this->font = font;

	wave.setFont(*font);
	score.setFont(*font);
	menuText.setFont(*font);
	menuText.setCharacterSize(40);
	menuText.setString("Вы проиграли");
	menuText.setPosition(this->window->getSize().x / 2 + menuText.getGlobalBounds().width / 2, 100);
}

DeathMenu::~DeathMenu()
{
}

void DeathMenu::setResults(float wave, float score)
{
	stringstream stream;
	stream << "Счёт: " << score;
	this->score.setString(stream.str());
	stream.str("");
	stream << "Волна: " << wave;
	this->wave.setString(stream.str());
	stream.str("");
}

void DeathMenu::setPosition(Vector2f pos)
{
	float centerX = (window->getSize().x - buttons["quit"]->getSize().x) / 2.f;
	menuText.setPosition(pos.x + this->window->getSize().x / 2 - menuText.getGlobalBounds().width / 2, pos.y + 100);
	score.setPosition(pos.x + this->window->getSize().x / 2 - score.getGlobalBounds().width / 2 - 100, pos.y + 180);
	wave.setPosition(pos.x + this->window->getSize().x / 2 - wave.getGlobalBounds().width / 2 + 100, pos.y + 180);

	this->buttons["restart"]->setPosition(Vector2f(pos.x + centerX, pos.y + 300.f));
	this->buttons["quit"]->setPosition(Vector2f(pos.x + centerX, pos.y + 450.f));
	this->background.setPosition(pos);
}

void DeathMenu::render(RenderTarget* target)
{
	target->draw(background);
	target->draw(menuText);
	target->draw(wave);
	target->draw(score);
	for (auto i : buttons)
	{
		i.second->render(target);
	}
}
