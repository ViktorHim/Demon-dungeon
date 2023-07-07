#include "Button.h"

Button::Button(Vector2f position, Vector2f size, string text, Font* font, Color mainColor, Color hoverColor)
{
	this->state = buttonState::idle;

	this->mainColor = mainColor;
	this->hoverColor = hoverColor;

	this->font = font;

	this->shape.setPosition(position);
	this->shape.setSize(size);
	this->shape.setFillColor(this->mainColor);

	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(Color::White);
	this->text.setCharacterSize(30);
	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height 
	);

}

Button::~Button()
{

}

void Button::setPosition(Vector2f position)
{
	this->shape.setPosition(position);
	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height 
	);
}

Vector2f Button::getSize()
{
	return shape.getSize();
}

const bool Button::isPressed()
{
	if (this->state == buttonState::pressed) return true;

	return false;
}

void Button::update( const Vector2f& mousePosition)
{
	this->state = buttonState::idle;

	if (this->shape.getGlobalBounds().contains(mousePosition))
	{
		this->state = buttonState::hover;

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			this->state = buttonState::pressed;
		}
	}

	switch (this->state)
	{
	case buttonState::hover:
	case buttonState::pressed:
		this->shape.setFillColor(this->hoverColor);
		break;
	default:
		this->shape.setFillColor(this->mainColor);
		break;
	}
}

void Button::render(RenderTarget* target)
{
	target->draw(this->shape);
	target->draw(this->text);
}