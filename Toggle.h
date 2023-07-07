#pragma once
#include "Entity.h"
class Toggle
{
private:
	void initStartState(bool state);

	RectangleShape backgroundShape;
	RectangleShape handleShape;

	Color bgColor;
	Color bgHandleColor;
	Color mainHandleColor;

	bool toggled;
	bool holdUp;
public:
	Toggle(Vector2f position, Vector2f size, Color bgColor, Color bgHandleColor, Color mainHandleColor, bool state);
	~Toggle();

	const bool isToggled();
	void toggle();

	void update(const Vector2f& mousePosition, Event event);
	void render(RenderTarget* target = nullptr);
};

