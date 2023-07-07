#include "Game.h"
#include "MainMenuState.h"

void Game::statesInit()
{
    states.push(new StartState(window, &states, &event, &gameData));
}

void Game::init()
{
	window =  new RenderWindow(VideoMode::getDesktopMode(), "Demon Dungeon");//создание окна
    window->setFramerateLimit(120);
    window->setVerticalSyncEnabled(true);
}

Game::Game()
{
    init();
    statesInit();
}

Game::~Game()
{
	delete window; //удаление окна

    while (!states.empty()) // удаление состояний
    {

        delete states.top();
        states.pop();
    }
}



//обновляющие методы
void Game::updateDt()
{
    dt = dtClock.restart().asSeconds(); //время между сменой кадров
}

void Game::updateEvents()// обновление событий
{
    while (window->pollEvent(event)) // обработка событий
    {
        switch (event.type)
        {
            case Event::Closed: //нажатие "крестика"
            {
                window->close();
            }
            break;
            default:
                break;
        }
    }
}

void Game::update()//обновление
{
    updateEvents();

    if (!states.empty()) // если стек не пуст обновляем первое состояние
    {
        states.top()->update(dt);

        if (states.top()->getQuit()) // если состояние завершено то извлечь его из стека
        {
            states.top()->endState();
            delete states.top();
            states.pop();
        }
    }
    else
    {
        window->close(); // если состояний нет окно закрывается
    }
}

void Game::render() //рендер
{
    window->clear();

    if (!states.empty()) // если стек не пуст рендерим первое состояние
    {
        states.top()->render();
    }

    window->display();
}

void Game::run() //запуск приложения
{
    while (window->isOpen()) {
        updateDt();
        update();
        render();
    }
}