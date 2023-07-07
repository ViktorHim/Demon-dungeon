#include "StartState.h"

void StartState::init()
{
	if (!font.loadFromFile(PIXEL_FONT))
	{
		throw("no font");
	}

	startWindow = new Preview(window, &font);
}

StartState::StartState(RenderWindow* window, stack<State*>* states,Event * event, Data* data) : State(window, states)
{
	this->event = event;
	gameData = data;
	this->window = window;
	this->states = states;
	this->isEnd = false;
	this->paused = false;
	init();
}

StartState::~StartState()
{
	delete startWindow;
}

void StartState::update(const float& dt)
{
	if (startWindow->getIsEnd())
	{
		states->pop();
		states->push(new MainMenuState(window, states, event, gameData));
	}
	else
	{
		startWindow->update();
	}
}

void StartState::updateInput(const float& dt)
{

}

void StartState::render(RenderTarget* target)
{
	startWindow->render(window);
}
