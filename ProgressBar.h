#pragma once
#include "Entity.h"
#include <string> 
#include <sstream>
enum barMode
{
	textMode,
	NumberMode
};

class ProgressBar
{
private:
	int mode;

	RectangleShape currentValueShape;
	RectangleShape maxValueShape;

	Font* font;
	Text text;

	Color mainColor;
	Color backColor;

	string textValue;
	ostringstream textStream;

	float length;
	float maxLength;
	float currentValue;
	float maxValue;
public:
	ProgressBar(Vector2f position, Vector2f size, Font* font, Color mainColor, Color backColor, float currentValue, float maxValue);
	ProgressBar(Vector2f position, Vector2f size, Font* font, Color mainColor, Color backColor, float currentValue, float maxValue, int mode);
	~ProgressBar();

	void setValue(float currentValue);
	void setPosition(Vector2f position);
	void setSize(Vector2f size);
	void setColor(Color mainColor, Color backColor);
	void setText(string text);
	void setFontSize(int size);

	void update();
	void render(RenderTarget* target = nullptr);
};

