#pragma once
#include "State.h"
#include "Preview.h"
#include "MainMenuState.h"
class StartState :
    public State
{
private:
    Preview* startWindow;
    Font font;
    Data* gameData;
    Event* event;
    void init();
public:
    //конструктор / деструктор
    StartState(RenderWindow* window, stack<State*>* states, Event* event, Data* data);
    virtual ~StartState();

    //обновление
    void update(const float& dt);
    void updateInput(const float& dt);

    //рендер
    void render(RenderTarget* target = nullptr);
};

