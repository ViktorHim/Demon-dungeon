#pragma once
#include "Entity.h"
#include "Button.h"
#include <sstream>
class BasicWindow
{
private:
protected:
	Font* font;
	Text menuText;

	RectangleShape background;
	RenderWindow* window;
	map<string, Button*> buttons;

public:
	BasicWindow(RenderWindow* window, Font* font);
	virtual ~BasicWindow();

	const bool isButtonPressed(const string key);
	void addButton(const std::string key, Vector2f position, Vector2f size, string text, Font* font, Color mainColor, Color hoverColor);
	virtual void update(const Vector2f& mousePosWindow);
	virtual void render(RenderTarget* target = nullptr);
};

