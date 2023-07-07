#include "Counter.h"

Counter::Counter(Vector2f position, Font* font, string text, int starValue)
{
	this->font = font;
	this->value = starValue;
	this->textValue = text;


	textStream << textValue << ": " << value;
	endValue = textStream.str();
	textStream.str("");
	textStream.clear();

	this->text.setString(endValue);
	this->text.setFont(*font);
	this->text.setFillColor(Color::White);
	this->text.setCharacterSize(25);
	setPosition(position);
}

Counter::Counter(Vector2f position, Font* font, string text)
{
	this->font = font;
	this->value = 0;
	this->textValue = text;

	textStream << textValue << ": " << value;
	endValue = textStream.str();
	textStream.str("");
	textStream.clear();

	this->text.setString(endValue);
	this->text.setFont(*font);
	this->text.setFillColor(Color::White);
	this->text.setCharacterSize(25);
	setPosition(position);
}

Counter::~Counter()
{
}

void Counter::setPosition(Vector2f position)
{
	this->text.setPosition(position);
}

void Counter::setValue(int newValue)
{
	this->value = newValue;
}

void Counter::addValue(int value)
{
	this->value += value;
}

int Counter::getValue()
{
	return value;
}

void Counter::update()
{
	textStream << textValue << ": " << value;
	endValue = textStream.str();
	textStream.str("");
	textStream.clear();
	this->text.setString(endValue);
}

void Counter::render(RenderTarget* target)
{
	target->draw(text);
}
