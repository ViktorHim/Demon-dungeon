#pragma once
#include "Entity.h"
#include <string> 
#include <sstream>
class Counter
{
private:
	Font* font;
	Text text;
	string textValue;
	string endValue;
	ostringstream textStream;
	int value;
public:
	Counter(Vector2f position, Font* font, string text, int starValue);
	Counter(Vector2f position, Font* font, string text);
	~Counter();

	void setPosition(Vector2f position);
	void setValue(int newValue);
	void addValue(int value);

	int getValue();

	void update();
	void render(RenderTarget* target = nullptr);
};

