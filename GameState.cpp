#include "GameState.h"
//������������� �������
void GameState::initTextures()
{
	if (!this->textures["tiles"].loadFromFile(MAIN_TEXTURE))
	{
		cout << "ERROR LOADIND TEXTURE FROM: " << MAIN_TEXTURE << endl;
	}
	//if (!this->textures["projectiles"].loadFromFile(PROJECTILES))
	//{
	//	cout << "ERROR LOADIND TEXTURE FROM: " << PROJECTILES << endl;
	//}
}

//������������� �����
void GameState::initTileMap()
{
	this->tilemap = new TileMap(16, 50, 50, 3.f, 3, &textures["tiles"]);

	this->tilemap->loadFromFile(GROUND_LAYER, 0); // ���� �����
	this->tilemap->loadFromFile(COLLISION_LAYER, 1); // ���� �� �������
	this->tilemap->loadFromFile(SPIKES_LAYER, 2); // ���� � ������
	bonusComponent = new BonusComponent(player, &textures["tiles"], tilemap);
	bonusComponent->setSettings(gameData->getSettings());
	bonusComponent->setSfx(gameData->getSfx());
}

void GameState::initEnemySystem()
{
	this->currentEnemy = nullptr;
	this->enemySystem = new EnemySystem(player, &gameScore, &textures["tiles"], bonusComponent);
	this->enemySystem->setFireballs(&bullets);
	this->enemySystem->setSettings(gameData->getSettings());
	this->enemySystem->setSfx(gameData->getSfx());
	this->enemies = enemySystem->getEnemies();
}

//������������� ������
void GameState::initPlayer()
{
	this->player = new Player(200.f, 300.f, &textures["tiles"], PLAYER_SPRITE_START, gameData->getPlayerData());
	this->player->shootComponent->setFireballs(&playerBullets);
	this->player->setSfx(gameData->getSfx());
	this->player->setSettings(gameData->getSettings());
}

//������������� ������
void GameState::initView()
{
	this->camera.setSize(this->window->getSize().x, this->window->getSize().y);
	this->camera.setCenter(this->window->getSize().x / 2.f, this->window->getSize().y / 2.f);
}

void GameState::initGui()
{
	if (!font.loadFromFile(PIXEL_FONT))
	{
		throw("no font");
	}

	bars["healthBar"] = new ProgressBar(Vector2f(50, 50), Vector2f(250, 30), &font, Color::Red, Color::Black, player->getHealth(), player->getMaxHealth());
	bars["manaBar"] = new ProgressBar(Vector2f(50, 100), Vector2f(250, 30), &font, Color::Blue, Color::Black, player->getMana(), player->getMaxMana());

	bonusBars["double"] = new ProgressBar(Vector2f(50, 250), Vector2f(250, 30), &font, Color::Yellow, Color::Black, 0, 10, barMode::textMode);
	bonusBars["double"]->setText("������� �������");
	bonusBars["double"]->setFontSize(15);
	bonusBars["triple"] = new ProgressBar(Vector2f(50, 300), Vector2f(250, 30), &font, Color::Green, Color::Black, 0, 10, barMode::textMode);
	bonusBars["triple"]->setText("������� �������");
	bonusBars["triple"]->setFontSize(15);
	bonusBars["speed"] = new ProgressBar(Vector2f(50, 350), Vector2f(250, 30), &font, Color::Cyan, Color::Black, 0, 10, barMode::textMode);
	bonusBars["speed"]->setText("���������");
	bonusBars["speed"]->setFontSize(15);



	counters["score"] = new Counter(Vector2f(50, 150), &font, "����");
	counters["wave"] = new Counter(Vector2f(50, 200), &font, "�����");

}

void GameState::initPauseMenu()
{
	Color mainColor = Color(81, 47, 102, 255);
	Color hoverColor = Color(128, 74, 161, 255);

	Vector2f size = Vector2f(300.f, 100.f);

	float centerX = (window->getSize().x - size.x) / 2.f;


	pauseMenu = new PauseMenu(window,&font);
	pauseMenu->addButton("resume", Vector2f(centerX, 300.f), size, "����������", &this->font, mainColor, hoverColor);
	pauseMenu->addButton("quit", Vector2f(centerX, 500.f), size, "�����", &this->font, mainColor, hoverColor);

	
}

void GameState::initDeathMenu()
{
	Color mainColor = Color(81, 47, 102, 255);
	Color hoverColor = Color(128, 74, 161, 255);

	Vector2f size = Vector2f(300.f, 100.f);

	float centerX = (window->getSize().x - size.x) / 2.f;

	deathMenu = new DeathMenu(window, &font);
	deathMenu->addButton("restart", Vector2f(centerX, 200.f), size, "������", &this->font, mainColor, hoverColor);
	deathMenu->addButton("quit", Vector2f(centerX, 400.f), size, "�����", &this->font, mainColor, hoverColor);
}

//�����������
GameState::GameState(RenderWindow* window, stack<State*>* states, Data * data) : State(window, states)
{
	this->gameData = data;
	gameOver = false;
	gameTime.restart();
	//������������� ���� ����������� ����
	this->initView();
	this->initTextures();

	this->initPlayer();
	this->initTileMap();
	this->initEnemySystem();


	this->player->shootComponent->setTargets(enemySystem->getEnemies());

	this->initGui();
	this->initPauseMenu();
	this->initDeathMenu();

	
	gameData->getMusic()->inGameMusic.play();
	gameData->getMusic()->inGameMusic.setLoop(true);

	if (!data->getSettings()->music)
	{
		gameData->getMusic()->inGameMusic.setVolume(0.f);
	}
	else
	{
		gameData->getMusic()->inGameMusic.setVolume(100.f);
	}
}

//����������
GameState::~GameState()
{
	delete this->player;
	delete this->tilemap;
}

//�������� � �������� �����
bool GameState::isNearBorder(float size, float pos, float windowSize)
{
	if ((pos < windowSize / 2.f) ||
		(pos > size - windowSize / 2.f))
	{
		return true;
	}
	return false;
}

void GameState::updaetGui(const float& dt)
{
	counters["score"]->setValue(gameScore);
	counters["score"]->update();
	counters["score"]->setPosition(Vector2f(camera.getCenter().x - camera.getSize().x / 2 + 50, camera.getCenter().y - camera.getSize().y / 2 + 150));

	counters["wave"]->setValue(enemySystem->getWaveNumber());
	counters["wave"]->update();
	counters["wave"]->setPosition(Vector2f(camera.getCenter().x - camera.getSize().x / 2 + 50, camera.getCenter().y - camera.getSize().y / 2 + 200));

	bars["healthBar"]->setPosition(Vector2f(camera.getCenter().x - camera.getSize().x / 2 + 50, camera.getCenter().y - camera.getSize().y / 2 + 50));
	bars["healthBar"]->setValue(player->getHealth());

	bars["manaBar"]->setPosition(Vector2f(camera.getCenter().x - camera.getSize().x / 2 + 50, camera.getCenter().y - camera.getSize().y / 2 + 100));
	bars["manaBar"]->setValue(player->getMana());

	int k = 0;
	map<string, float> time = *bonusComponent->getRemainingTime();
	for (auto i : bonusBars)
	{
		if (time[i.first] > 0.f)
		{
			i.second->setPosition(Vector2f(camera.getCenter().x - camera.getSize().x / 2 + 50, camera.getCenter().y - camera.getSize().y / 2 + 250 + k++ * 50));
			i.second->setValue(time[i.first]);
			i.second->update();
		}
	}

	for (auto i : bars)
	{
		i.second->update();
	}
}

//���������� ������
void GameState::updateView(const float& dt)
{
	if (!this->isNearBorder(this->tilemap->getSize().x , this->player->getPosition().x, this->window->getSize().x))
	{
		this->camera.setCenter(this->player->getPosition().x, this->camera.getCenter().y); 
		// ���� �� ��� x ����� ���������� ������ �� ������ �� ������������� ����� ������ �� ���������� ������ �� ��� x
	}
	if (!this->isNearBorder(this->tilemap->getSize().y , this->player->getPosition().y, this->window->getSize().y))
	{
		this->camera.setCenter(this->camera.getCenter().x, this->player->getPosition().y);
		// ���� �� ��� y ����� ���������� ������ �� ������ �� ������������� ����� ������ �� ���������� ������ �� ��� y
	}
}

void GameState::updatePausedInput(const float& dt)
{
	pauseMenu->update(mousePosView);
	pauseMenu->setPosition(Vector2f(camera.getCenter().x - camera.getSize().x / 2, camera.getCenter().y - camera.getSize().y / 2));

	if (pauseMenu->isButtonPressed("resume"))
	{
		unpauseState();
	}
	if (pauseMenu->isButtonPressed("quit"))
	{
		if (gameScore != 0)
		{
			gameData->addScore(gameScore);
		}
		gameData->getMusic()->inGameMusic.stop();
		this->window->setView(this->window->getDefaultView()); // ��������� ������ � ��������� �������
		endState();
	}
}

void GameState::updateDeathInput(const float& dt)
{
	deathMenu->setResults(enemySystem->getWaveNumber(), gameScore);
	deathMenu->setPosition(Vector2f(camera.getCenter().x - camera.getSize().x / 2, camera.getCenter().y - camera.getSize().y / 2));
	deathMenu->update(mousePosView);

	if (deathMenu->isButtonPressed("restart"))
	{
		gameData->getMusic()->inGameMusic.stop();
		gameData->addScore(gameScore);
		states->pop();
		states->push(new GameState(window, states, gameData));
	}
	if (deathMenu->isButtonPressed("quit"))
	{
		gameData->getMusic()->inGameMusic.stop();

		if (gameScore != 0)
		{
			gameData->addScore(gameScore);
		}
		this->window->setView(this->window->getDefaultView()); // ��������� ������ � ��������� �������
		endState();
	}
}

//���������� �����
void GameState::updateInput(const float& dt)
{

	if (Keyboard::isKeyPressed(Keyboard::Escape)) // ��� ������� escape ��������� �����������
	{
		if (!paused)
		{
			this->pauseState();
		}
	}
}

void GameState::updateTileMap(const float& dt)
{
	this->tilemap->update(dt);
	this->tilemap->updateCollisionBounds(this->player);
	this->tilemap->updateTileCollision(this->player, dt);

	for (int i = 0; i < enemies->size(); i++)
	{
		currentEnemy = enemies->front();
		enemies->pop();

		this->tilemap->updateCollisionBounds(currentEnemy);
		this->tilemap->updateEnemyTileCollision(currentEnemy, dt);

		enemies->push(currentEnemy);
	}
	//cout << bullets.size() << endl;
	if (!bullets.empty())
	{
		for (int i = 0; i < bullets.size(); i++)
		{
			queue<Fireball*>* que = bullets.front();
			bullets.pop();

			if (que && !que->empty())
			{
				for (int j = 0; j < que->size(); j++)
				{
					Fireball* currentFireball = que->front();
					que->pop();
					this->tilemap->updateTileCollision(currentFireball, dt);
					que->push(currentFireball);
				}
			}
			
			bullets.push(que);
		}
	}
	

	for (int i = 0; i < playerBullets.size(); i++)
	{
		Fireball* currentFireball = playerBullets.front();
		playerBullets.pop();
		this->tilemap->updateTileCollision(currentFireball, dt);
		playerBullets.push(currentFireball);
	}
}

void GameState::updateEntity(const float& dt)
{
	enemySystem->update(dt);
}

//���������� ���� ����������� ����
void GameState::update(const float& dt)
{
	this->updateMousePosition();

	if (player->getHealth() == 0)
	{
		this->updateDeathInput(dt);
		if (!gameOver) this->updaetGui(dt);
		gameOver = true;
	}
	else
	{
		if (!paused)
		{
			bonusComponent->update(dt);
			this->updateInput(dt);
			updateTileMap(dt);
			this->player->update(dt);
			this->player->shootUpdate(&mousePosView, dt);
			this->updateView(dt);
			this->updaetGui(dt);
			this->updateEntity(dt);
		}
		else
		{
			this->updatePausedInput(dt);
		}
	}
}

//������ ���� ����������� ����
void GameState::render(RenderTarget* target)
{
	if (!target)
	{
		target = window;
	}

	target->setView(this->camera); // ����������� ������ �����

	this->tilemap->render(*target); // ������ �����
	this->bonusComponent->render(target);
	this->player->render(target); // ������ ������
	renderEnemies(target); // ������ �����������
	renderGUI(target); // ������ ����������
	renderWindows(target); //������ ����


}

void GameState::renderGUI(RenderTarget* target)
{
	for (auto i : bars)
	{
		i.second->render(target);
	}

	for (auto i : counters)
	{
		i.second->render(target);
	}

	map<string, float> time = *bonusComponent->getRemainingTime();
	for (auto i : bonusBars)
	{

		if (time[i.first] > 0.f)
		{
			i.second->render(target);
		}
	}
}

void GameState::renderWindows(RenderTarget* target)
{
	if (paused)
	{
		pauseMenu->render(target);
	}
	if (gameOver)
	{
		deathMenu->render(target);
	}
}

void GameState::renderEnemies(RenderTarget* target)
{
	enemySystem->render(target);
}