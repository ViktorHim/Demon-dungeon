#include "State.h"

//конструктор
State::State(RenderWindow* window, stack<State*>* states)
{
	this->window = window;
	this->states = states;
	this->isEnd = false;
	this->paused = false;
}

//деструктор
State::~State()
{

}

//проверка об окочании состояния
const bool& State::getQuit() const //возвращает флаг выхода
{
	return isEnd;
}

//закончить состояние
void State::endState()
{
	isEnd = true;
}

void State::pauseState()
{
	paused = true;
}

void State::unpauseState()
{
	paused = false;
}

//обновление позиции мыши
void State::updateMousePosition()
{
	this->mousePosScreen = Mouse::getPosition();
	this->mousePosView = this->window->mapPixelToCoords(Mouse::getPosition(*this->window));
}