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

	stack <State*> states; // стек состояний

	void statesInit(); // инициализация состояний
	void init(); // инициализация окна
public:
	Game();
	virtual ~Game();

	void updateDt();//обновляющие методы
	void updateEvents();
	void update();

	void render();

	void run();

};