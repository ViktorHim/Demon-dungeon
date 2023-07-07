#pragma once
#include "BasicWindow.h"
class DeathMenu :
    public BasicWindow
{
private:
	Text wave;
	Text score;
public:
	DeathMenu(RenderWindow* window, Font* font);
	virtual ~DeathMenu();
	void setResults(float wave, float score);
	void setPosition(Vector2f pos);
	void render(RenderTarget* target = nullptr);
};

