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
   Sprite background;//спрайт фона
   Texture textureBg;//тексура фона
   Font font;//шрифт
   Event * event;
   Text title;//название игры
   Text greeting;//приветствие
   Data* gameData;

   RecordsWindow * records;
   HelpWindow* help;
   PlayerWindow* playerWindow;
   int activeWindow;

    map <string ,Button*> buttons;//кнопки
    map<string, Toggle*> toggles;//переключатели
    map<string, Text*> texts;//надписи
    map<string, Color> colors;

    bool pressed;

    Vector2f buttonSize;
    float centerX;

    void init();// инициализация
    void initMusic();
    void initMainWindow();
    void initRecords();
    void initHelp();
    void initPlayerWindow();
public:
    //конструктор / деструктор
    MainMenuState(RenderWindow* window, stack<State*>* states, Event * event, Data * data);
    virtual ~MainMenuState();
    //обновление
    void updateInput(const float& dt);
    void updateRecords(const float& dt);
    void updateHelp(const float& dt);
    void updatePlayerWindow(const float& dt);
    void updateButtons();
    void updateToggles();
    void update(const float& dt);
    //рендер
    void renderButtons(RenderTarget* target = nullptr);
    void render(RenderTarget* target = nullptr);
};