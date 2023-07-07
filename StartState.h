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
    //����������� / ����������
    StartState(RenderWindow* window, stack<State*>* states, Event* event, Data* data);
    virtual ~StartState();

    //����������
    void update(const float& dt);
    void updateInput(const float& dt);

    //������
    void render(RenderTarget* target = nullptr);
};

