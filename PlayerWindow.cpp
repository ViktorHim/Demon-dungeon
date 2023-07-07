#include "PlayerWindow.h"

PlayerWindow::PlayerWindow(RenderWindow* window, Font* font, Event * event) : BasicWindow(window, font)
{
	this->textChanged = false;
	this->window = window;
	background.setSize(Vector2f(this->window->getSize().x / 3, this->window->getSize().y / 3));
	background.setPosition(
		Vector2f((this->window->getSize().x - background.getSize().x) / 2,
				 (this->window->getSize().y - background.getSize().y) / 2));
	background.setFillColor(Color(20, 20, 20, 200));
	this->font = font;

	menuText.setFont(*font);
	menuText.setString("¬ведите новое им€:");
	menuText.setPosition(background.getPosition().x + menuText.getGlobalBounds().width / 3, background.getPosition().y + 20);

	textField.setSize(Vector2f(background.getSize().x * 0.8, 50));
	textField.setPosition(background.getPosition().x + background.getSize().x / 2 - textField.getSize().x / 2, background.getPosition().y + background.getSize().y / 2 - textField.getSize().y / 2);

	text.setFont(*font);
	text.setFillColor(Color::Black);
	text.setPosition(textField.getPosition().x + 10, textField.getPosition().y);

	this->event = event;
	str = "";
	lengthInput = 15;
}

PlayerWindow::~PlayerWindow()
{
}


string PlayerWindow::getString()
{
	string strr = str;
	while ((strr.size() > 0) && strr[strr.size()-1] == ' ')
	{
		strr.pop_back();
	}
	return strr;
}

void PlayerWindow::clearString()
{
	str = "";
}

void PlayerWindow::render(RenderTarget* target)
{
	target->draw(background);
	target->draw(menuText);
	target->draw(textField);
	target->draw(text);
	for (auto i : buttons)
	{
		i.second->render(target);
	}
}

void PlayerWindow::update(const Vector2f& mousePosWindow)
{
		if (Keyboard::isKeyPressed(Keyboard::BackSpace))
		{
			if (str.size() > 0)
			{
				str.pop_back();
			}
		}
		else if (event->type == Event::TextEntered && str.size() <= lengthInput && event->text.unicode < 128 && !textChanged)
		{
			str += event->text.unicode;
			textChanged = true;
		}
		else if (event->type == Event::TextEntered && str.size() <= lengthInput && event->text.unicode < 128 && event->text.unicode != str[str.size()-1])
		{
			str += event->text.unicode;
			textChanged = true;
		}
		if (event->type == Event::KeyReleased)
		{
			textChanged = false;
		}
	
		text.setString(str);

	for (auto& i : this->buttons)
	{
		i.second->update(mousePosWindow);
	}
}
