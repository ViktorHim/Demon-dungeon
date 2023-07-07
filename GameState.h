#pragma once

#include "State.h"
#include "Player.h"
#include "TileMap.h"
#include "DataPaths.h"
#include "ProgressBar.h"
#include "Counter.h"
#include "PauseMenu.h"
#include "TinyDemon.h"
#include "Demon.h"
#include "HugeDemon.h"
#include "Data.h"
#include "EnemySystem.h"
#include <queue>
#include "BonusComponent.h"
#include "DeathMenu.h"
class GameState :
    public State
{
private:
    //�������������
    void initTextures();
    void initTileMap(); 
    void initEnemySystem();
    void initPlayer(); 
    void initView();
    void initGui();
    void initPauseMenu();
    void initDeathMenu();

    ShootComponent* enemyShoot;
    BonusComponent* bonusComponent;
    EnemySystem* enemySystem;
    queue<Enemy*>* enemies;
    Enemy* currentEnemy;

    queue<queue<Fireball*>*> bullets;//�������
    queue<Fireball*> playerBullets;

    TileMap* tilemap; // �����
    Player* player; // �����

    Font font;//�����
    View camera; // ������
    Clock gameTime;
    Data* gameData;

    map <string, ProgressBar*> bars; // �������������� ���������
    map <string, ProgressBar*> bonusBars;//������������ �������
    map <string, Counter*> counters; 
    PauseMenu* pauseMenu;//���� �����
    DeathMenu* deathMenu;//���� ������

    float gameScore;
    bool gameOver;
public:
    // ����������� / ����������
    GameState(RenderWindow* window, stack<State*>* states, Data * data);
    virtual ~GameState();

    //��������
    bool isNearBorder(float size, float pos, float windowSize);

    //����������
    void updaetGui(const float& dt);
    void updateView(const float& dt);
    void updatePausedInput(const float& dt);
    void updateDeathInput(const float& dt);
    void updateInput(const float& dt);
    void updateTileMap(const float& dt);
    void updateEntity(const float& dt);
    void update(const float& dt);

    //������
    void render(RenderTarget* target = nullptr);
    void renderGUI(RenderTarget* target);
    void renderWindows(RenderTarget* target);
    void renderEnemies(RenderTarget* target);
};