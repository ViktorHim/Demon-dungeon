#include "State.h"

//�����������
State::State(RenderWindow* window, stack<State*>* states)
{
	this->window = window;
	this->states = states;
	this->isEnd = false;
	this->paused = false;
}

//����������
State::~State()
{

}

//�������� �� �������� ���������
const bool& State::getQuit() const //���������� ���� ������
{
	return isEnd;
}

//��������� ���������
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

//���������� ������� ����
void State::updateMousePosition()
{
	this->mousePosScreen = Mouse::getPosition();
	this->mousePosView = this->window->mapPixelToCoords(Mouse::getPosition(*this->window));
}