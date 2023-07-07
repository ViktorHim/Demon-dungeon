#pragma once
#include "BasicWindow.h"
class PauseMenu : public BasicWindow
{
private:

public:
	PauseMenu(RenderWindow* window,Font* font);
	virtual ~PauseMenu();

	void setPosition(Vector2f pos);
	
};

