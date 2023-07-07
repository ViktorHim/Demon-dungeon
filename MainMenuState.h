#pragma once
#include "State.h"
#include "GameState.h"
#include "Button.h"
#include "PlayerWindow.h"
#include "HelpWindow.h"
#include "RecordsWindow.h"
#include "Toggle.h"
#include "Data.h"
#include <sstream>

enum windows
{
    mainn,
    records,
    help,
    player
};

class MainMenuState :
    public State
{
private:
   Sprite background;//������ ����
   Texture textureBg;//������� ����
   Font font;//�����
   Event * event;
   Text title;//�������� ����
   Text greeting;//�����������
   Data* gameData;

   RecordsWindow * records;
   HelpWindow* help;
   PlayerWindow* playerWindow;
   int activeWindow;

    map <string ,Button*> buttons;//������
    map<string, Toggle*> toggles;//�������������
    map<string, Text*> texts;//�������
    map<string, Color> colors;

    bool pressed;

    Vector2f buttonSize;
    float centerX;

    void init();// �������������
    void initMusic();
    void initMainWindow();
    void initRecords();
    void initHelp();
    void initPlayerWindow();
public:
    //����������� / ����������
    MainMenuState(RenderWindow* window, stack<State*>* states, Event * event, Data * data);
    virtual ~MainMenuState();
    //����������
    void updateInput(const float& dt);
    void updateRecords(const float& dt);
    void updateHelp(const float& dt);
    void updatePlayerWindow(const float& dt);
    void updateButtons();
    void updateToggles();
    void update(const float& dt);
    //������
    void renderButtons(RenderTarget* target = nullptr);
    void render(RenderTarget* target = nullptr);
};