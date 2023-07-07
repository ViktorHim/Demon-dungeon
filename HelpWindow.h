#pragma once
#include "BasicWindow.h"
#include <string> 
#include <sstream>

struct item
{
	Texture texture;
	Sprite sprite;
};
class HelpWindow : public BasicWindow
{
private:
	map<string, Text> text;
	map<string, item> images;
	RectangleShape divideShape;

public:
	HelpWindow(RenderWindow* window, Font* font);
	~HelpWindow();
	void addImage(string path, string key,Vector2f scale, Vector2f pos);
	void addText(string key, string textValue, Vector2f pos);

	void render(RenderTarget* target = nullptr);

};

