#include "BasicWindow.h"

BasicWindow::BasicWindow(RenderWindow* window, Font* font)
{
	this->window = window;
	background.setSize(Vector2f(this->window->getSize().x, this->window->getSize().y));
	background.setFillColor(Color(20, 20, 20, 200));
	this->font = font;
}

BasicWindow::~BasicWindow()
{

}

const bool BasicWindow::isButtonPressed(const string key)
{
	return buttons[key]->isPressed();
}

void BasicWindow::addButton(const std::string key, Vector2f position, Vector2f size, string text, Font* font, Color mainColor, Color hoverColor)
{
	buttons[key] = new Button(position, size, text, font, mainColor, hoverColor);
}

void BasicWindow::update(const Vector2f& mousePosWindow)
{
	for (auto& i : this->buttons)
	{
		i.second->update(mousePosWindow);
	}
}

void BasicWindow::render(RenderTarget* target)
{
	target->draw(background);
	target->draw(menuText);
	for (auto i : buttons)
	{
		i.second->render(target);
	}
}


