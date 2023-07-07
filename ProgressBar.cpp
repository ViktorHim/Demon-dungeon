#include "ProgressBar.h"

ProgressBar::ProgressBar(Vector2f position, Vector2f size, Font* font, Color mainColor, Color backColor, float currentValue, float maxValue)
{
	this->mode = barMode::NumberMode;
	this->currentValue = currentValue;
	this->maxValue = maxValue;
	setPosition(position);
	setSize(size);
	setColor(mainColor, backColor);

	textStream << (int)currentValue << " / " << (int)maxValue;
	textValue = textStream.str();
	textStream.str("");
	textStream.clear();

	this->text.setString(textValue);
	text.setFont(*font);
	this->text.setFillColor(Color::White);
	this->text.setCharacterSize(25);
	this->text.setPosition(
		this->maxValueShape.getPosition().x + (this->maxValueShape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		this->maxValueShape.getPosition().y + (this->maxValueShape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height);
}

ProgressBar::ProgressBar(Vector2f position, Vector2f size, Font* font, Color mainColor, Color backColor, float currentValue, float maxValue, int mode)
{
	this->mode = mode;
	this->currentValue = currentValue;
	this->maxValue = maxValue;
	setPosition(position);
	setSize(size);
	setColor(mainColor, backColor);

	if (mode == barMode::NumberMode)
	{
		textStream << (int)currentValue << " / " << (int)maxValue;
		textValue = textStream.str();
		textStream.str("");
		textStream.clear();
	}
	

	this->text.setString(textValue);
	text.setFont(*font);
	this->text.setFillColor(Color::White);
	this->text.setCharacterSize(25);
	this->text.setPosition(
		this->maxValueShape.getPosition().x + (this->maxValueShape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		this->maxValueShape.getPosition().y + (this->maxValueShape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height);
}

ProgressBar::~ProgressBar()
{

}

void ProgressBar::setValue(float currentValue)
{
	if (currentValue <= 0)
	{
		this->currentValue = 0.f;

	}
	else
	{
		this->currentValue = currentValue;
	}
}

void ProgressBar::setPosition(Vector2f position)
{
	currentValueShape.setPosition(position);
	maxValueShape.setPosition(position);
	this->text.setPosition(
		this->maxValueShape.getPosition().x + (this->maxValueShape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		this->maxValueShape.getPosition().y + (this->maxValueShape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height);
}

void ProgressBar::setSize(Vector2f size)
{
	maxLength = size.x;
	length = maxLength * (currentValue / maxValue);
	currentValueShape.setSize(Vector2f(length, size.y));
	maxValueShape.setSize(size);
}

void ProgressBar::setColor(Color mainColor, Color backColor)
{
	this->mainColor = mainColor;
	this->backColor = backColor;

	currentValueShape.setFillColor(this->mainColor);
	maxValueShape.setFillColor(this->backColor);
}

void ProgressBar::setText(string text)
{
	this->textValue = text;
}

void ProgressBar::setFontSize(int size)
{
	this->text.setCharacterSize(size);
}

void ProgressBar::update()
{
	length = maxLength * (currentValue / maxValue);
	currentValueShape.setSize(Vector2f(length, currentValueShape.getSize().y));

	if (mode == barMode::NumberMode)
	{
		textStream << (int)currentValue << " / " << (int)maxValue;
		textValue = textStream.str();
		textStream.str("");
		textStream.clear();
	}

	this->text.setString(textValue);
}

void ProgressBar::render(RenderTarget* target)
{
	target->draw(maxValueShape);
	target->draw(currentValueShape);
	target->draw(text);
}
