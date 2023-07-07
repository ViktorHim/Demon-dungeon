#include "RecordsWindow.h"

RecordsWindow::RecordsWindow(RenderWindow* window, Font* font, vector<pair<int, string>>* records) : BasicWindow(window, font)
{
	this->window = window;
	background.setSize(Vector2f(this->window->getSize().x, this->window->getSize().y));
	background.setFillColor(Color(20, 20, 20, 255));
	this->font = font;
	this->records = records;

	ostringstream str;
	int k = 1;
	Vector2f pos = Vector2f(0.f, 0.f);

	if (records->empty())
	{
		Text text = Text("Список рекордов пуст", *font, 30);
		text.setPosition(pos);
		recordsText.push_back(text);
	}
	else
	{
		for (auto i : *records)
		{
			str << k++ << ". " << i.second << ": " << i.first;
			Text text = Text(str.str(), *font, 30);
			text.setPosition(pos.x, pos.y);
			text.setFont(*font);
			pos.y += 50;

			recordsText.push_back(text);
			str.str("");
			str.clear();
		}
	}
}

RecordsWindow::~RecordsWindow()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}



void RecordsWindow::render(RenderTarget* target)
{
	target->draw(background);

	for (auto i : buttons)
	{
		i.second->render(target);
	}

	for (auto i : recordsText)
	{
		target->draw(i);
	}
}

void RecordsWindow::refresh()
{
	recordsText.clear();
	ostringstream str;
	int k = 1;
	Vector2f pos = Vector2f(0.f, 0.f);
	recordsText.clear();
	if (records->empty())
	{
		Text text = Text("Список рекордов пуст", *font, 30);
		text.setPosition(pos);
		recordsText.push_back(text);
	}
	else
	{
		for (auto i : *records)
		{
			str << k++ << ". " << i.second << ": " << i.first;
			Text text = Text(str.str(), *font, 30);
			text.setPosition(pos.x, pos.y);
			text.setFont(*font);
			pos.y += 50;

			recordsText.push_back(text);
			str.str("");
			str.clear();
		}
	}
}
