#pragma once
#include "Data.h"
#include "GameState.h"
#include "StartState.h"
class Game
{
private:
	RenderWindow* window;
	Event event;
	Data gameData;
	float dt;
	Clock dtClock;

	stack <State*> states; // ���� ���������

	void statesInit(); // ������������� ���������
	void init(); // ������������� ����
public:
	Game();
	virtual ~Game();

	void updateDt();//����������� ������
	void updateEvents();
	void update();

	void render();

	void run();

};