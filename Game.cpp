#include "Game.h"
#include "MainMenuState.h"

void Game::statesInit()
{
    states.push(new StartState(window, &states, &event, &gameData));
}

void Game::init()
{
	window =  new RenderWindow(VideoMode::getDesktopMode(), "Demon Dungeon");//�������� ����
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
	delete window; //�������� ����

    while (!states.empty()) // �������� ���������
    {

        delete states.top();
        states.pop();
    }
}



//����������� ������
void Game::updateDt()
{
    dt = dtClock.restart().asSeconds(); //����� ����� ������ ������
}

void Game::updateEvents()// ���������� �������
{
    while (window->pollEvent(event)) // ��������� �������
    {
        switch (event.type)
        {
            case Event::Closed: //������� "��������"
            {
                window->close();
            }
            break;
            default:
                break;
        }
    }
}

void Game::update()//����������
{
    updateEvents();

    if (!states.empty()) // ���� ���� �� ���� ��������� ������ ���������
    {
        states.top()->update(dt);

        if (states.top()->getQuit()) // ���� ��������� ��������� �� ������� ��� �� �����
        {
            states.top()->endState();
            delete states.top();
            states.pop();
        }
    }
    else
    {
        window->close(); // ���� ��������� ��� ���� �����������
    }
}

void Game::render() //������
{
    window->clear();

    if (!states.empty()) // ���� ���� �� ���� �������� ������ ���������
    {
        states.top()->render();
    }

    window->display();
}

void Game::run() //������ ����������
{
    while (window->isOpen()) {
        updateDt();
        update();
        render();
    }
}