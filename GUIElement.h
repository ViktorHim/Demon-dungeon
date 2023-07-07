#include "Entity.h"

#pragma once
class GUIElement
{
private:
	int state;
	Color* colors;

protected:
public:
	GUIElement();
	virtual ~GUIElement();

	virtual const bool isPressed() = 0;

	virtual void update(const Vector2f& mousePosition) = 0;
	virtual void render(RenderTarget* target = nullptr) = 0;
};