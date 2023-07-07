#pragma once
#include "BasicWindow.h"
class Preview : public BasicWindow
{
private:
	float animationTime;
	float endScale;
	Clock timer;
	bool isEnd;
public:
	Preview(RenderWindow* window, Font* font);
	virtual ~Preview();
	void update();
	bool getIsEnd();
	void render(RenderTarget* target = nullptr);
};

