#pragma once

#include <string> 
#include <sstream>
#include "BasicWindow.h"
class RecordsWindow : public BasicWindow
{
private:
	vector<pair<int, string>>* records;
	vector<Text> recordsText;

public:
	RecordsWindow(RenderWindow* window, Font* font, vector<pair<int, string>>* records);
	virtual ~RecordsWindow();
	void render(RenderTarget* target = nullptr);

	void refresh();
};

