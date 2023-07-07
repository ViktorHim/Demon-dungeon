#pragma once
#include "GUIElement.h"
enum buttonState
{
	idle,
	hover,
	pressed
};

class Button
{
private:
	int state;

	RectangleShape shape;
	Font* font;
	Text text;

	Color mainColor;
	Color hoverColor;

protected:
public:
	Button(Vector2f position, Vector2f size, string text, Font * font, Color mainColor, Color hoverColor);
	virtual ~Button();
	void setPosition(Vector2f position);
	Vector2f getSize();
	const bool isPressed();

	void update(const Vector2f& mousePosition);
	void render(RenderTarget* target = nullptr);
};