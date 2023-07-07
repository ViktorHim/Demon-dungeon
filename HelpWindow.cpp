#include "HelpWindow.h"

HelpWindow::HelpWindow(RenderWindow* window, Font* font) : BasicWindow(window, font)
{
	this->window = window;
	background.setSize(Vector2f(this->window->getSize().x, this->window->getSize().y));
	background.setFillColor(Color(20, 20, 20, 200));
	this->font = font;

	float centerX = window->getSize().x / 2;

	divideShape.setSize(Vector2f(10, 1000));
	divideShape.setPosition(centerX - 200, 0);
	divideShape.setFillColor(Color::White);

	addImage(
		WASD,
		"wasd",
		Vector2f(0.3f, 0.3f),
		Vector2f(30, 50)
	);
	addImage(
		ARROWS,
		"arrows",
		Vector2f(0.95f, 0.95f),
		Vector2f(230, 40)
	);
	addImage(
		SHOOT,
		"shoot",
		Vector2f(0.8f, 0.8f),
		Vector2f(30, 300)
	);
	addImage(
		ESC,
		"esc",
		Vector2f(0.2f, 0.2f),
		Vector2f(30, 570)
	);

	addText("wasd", "���������� ����������: ", Vector2f(30, 30));
	addText("shoot", "��������: ", Vector2f(30, 250));
	addText("pause", "�����: ", Vector2f(30, 520));
	addText("rules", "������� ����", Vector2f(divideShape.getPosition().x + 50, 30));
	addText("rulesText", 
		"���� ����: ������������ �� ����� ��� ����� ������.\n\n�����:\n- ����� �������� �������\n- ����� ������������� ��� ������ �������� ��� �������\n- � ����������� ����� ����� ���������\n\n�����:\n- ������ 10 ��� �� ����� ���������� ��������� �����, ���� ��\n�������� �� �����\n- ����� ���������� 5 ����� �����:\n 1 ��������\n 2 ����\n 3 ��������\n 4 �������� ��������\n 5 �������� ��������\n- ������ 5 ���� ���������� ����� ��������", 
		Vector2f(divideShape.getPosition().x + 50, 100));
	text["rulesText"].setCharacterSize(25);
}

HelpWindow::~HelpWindow()
{

}

void HelpWindow::addImage(string path, string key, Vector2f scale, Vector2f pos)
{
	images[key].texture.loadFromFile(path);
	images[key].sprite.setTexture(images[key].texture);
	images[key].sprite.setScale(scale);
	images[key].sprite.setPosition(pos);
}

void HelpWindow::addText(string key,string textValue, Vector2f pos)
{
	text[key].setFont(*font);
	text[key].setString(textValue);
	text[key].setPosition(pos);

}

void HelpWindow::render(RenderTarget* target)
{
	target->draw(background);
	target->draw(divideShape);
	for (auto i : buttons)
	{
		i.second->render(target);
	}
	for (auto i : images)
	{
		target->draw(i.second.sprite);
	}

	for (auto i : text)
	{
		target->draw(i.second);
	}
}
