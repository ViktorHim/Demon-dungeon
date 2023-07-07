#pragma once
#include "BasicWindow.h"
#include <string> 
#include <sstream>
class PlayerWindow : public BasicWindow
{
private:
	RectangleShape textField;
	Text text;
	string str;
	Event* event;
	int lengthInput;
	bool textChanged;
	
public:
	PlayerWindow(RenderWindow* window, Font* font, Event * event);
	~PlayerWindow();
	
	string getString();
	void clearString();
	void render(RenderTarget* target = nullptr);
	void update(const Vector2f& mousePosWindow);
};

