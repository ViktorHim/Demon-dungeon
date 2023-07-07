#include "MainMenuState.h"
void MainMenuState::initMusic()
{
	gameData->getMusic()->menuMusic.play();
	gameData->getMusic()->menuMusic.setLoop(true);

	if (!gameData->getSettings()->music)
	{
		gameData->getMusic()->menuMusic.setVolume(0.f);
	}
	else
	{
		gameData->getMusic()->menuMusic.setVolume(100.f);
	}
}
void MainMenuState::initMainWindow()
{
	textureBg.loadFromFile(MAIN_MENU_BACKGROUND);
	background.setTexture(textureBg);
	background.setScale(Vector2f(4.2f, 4.2f));

	Vector2f toggleSize = Vector2f(90.f, 30.f);
	Vector2f togglePosition = Vector2f(window->getSize().x - toggleSize.x, window->getSize().y - toggleSize.y - 100);

	float posY = 300.f;
	float offset = 100.f;

	//создание кнопок
	buttons["play"] = new Button(Vector2f(centerX, posY), buttonSize, "Играть", &this->font, colors["mainColor"], colors["hoverColor"]);
	buttons["player"] = new Button(Vector2f(centerX, posY += offset), buttonSize, "Новый игрок", &this->font, colors["mainColor"], colors["hoverColor"]);
	buttons["help"] = new Button(Vector2f(centerX, posY += offset), buttonSize, "Справка", &this->font, colors["mainColor"], colors["hoverColor"]);
	buttons["records"] = new Button(Vector2f(centerX, posY += offset), buttonSize, "Рекорды", &this->font, colors["mainColor"], colors["hoverColor"]);
	buttons["exit"] = new Button(Vector2f(centerX, posY += offset), buttonSize, "Выход", &this->font, colors["mainColor"], colors["hoverColor"]);

	//создание переключателей
	togglePosition.y -= 100;
	togglePosition.x -= 500;
	texts["sfx"] = new Text("Звуковые эффекты", font, 30);
	texts["sfx"]->setPosition(togglePosition);

	togglePosition.x += 350;
	toggles["sfx"] = new Toggle(togglePosition, toggleSize, colors["bgColor"], colors["bgColorActive"], colors["mainColor"], gameData->getSettings()->sfx);

	togglePosition.x -= 150;
	togglePosition.y -= 100;
	texts["music"] = new Text("Музыка", font, 30);
	texts["music"]->setPosition(togglePosition);

	togglePosition.x += 150;
	toggles["music"] = new Toggle(togglePosition, toggleSize, colors["bgColor"], colors["bgColorActive"], colors["mainColor"], gameData->getSettings()->music);

	title.setFont(font);
	title.setCharacterSize(60);
	title.setString("Ужасные подземелья");
	title.setPosition(window->getSize().x / 2 - title.getGlobalBounds().width / 2, 50);

	greeting.setFont(font);
	greeting.setCharacterSize(35);

	stringstream stream;
	stream << "Приветствуем, " << gameData->getPlayerData()->nickname;
	greeting.setString(stream.str());
	stream.str("");

	greeting.setPosition(window->getSize().x / 2 - greeting.getGlobalBounds().width / 2, 180);

	
}
//инициализация
void MainMenuState::init()
{

	if (!font.loadFromFile(PIXEL_FONT))
	{
		throw("no font");
	}
	activeWindow = windows::mainn;

	colors["mainColor"] = Color(81, 47, 102, 255);
	colors["hoverColor"] = Color(128, 74, 161, 255);
	colors["bgColor"] = Color(191, 187, 174, 255);
	colors["bgColorActive"] = Color(121, 242, 170, 255);

	buttonSize = Vector2f(300.f, 90.f);
	centerX = (window->getSize().x - buttonSize.x) / 2.f;
}

void MainMenuState::initRecords()
{
	records = new RecordsWindow(window, &font, gameData->getBestScores());
	records->addButton("delete", Vector2f(centerX + 300, 650.f), buttonSize, "Очистить", &this->font, colors["mainColor"], colors["hoverColor"]);
	records->addButton("quit", Vector2f(centerX - 300, 650.f), buttonSize, "Назад", &this->font, colors["mainColor"], colors["hoverColor"]);
}

void MainMenuState::initHelp()
{
	help = new HelpWindow(window, &font);
	help->addButton("quit", Vector2f(centerX, 700.f), buttonSize, "Назад", &this->font, colors["mainColor"], colors["hoverColor"]);
}

void MainMenuState::initPlayerWindow()
{
	Vector2f size = Vector2f(200, 70);
	playerWindow = new PlayerWindow(window, &font, event);
	playerWindow->addButton("ok", Vector2f(centerX + 200, 500.f), size, "Ок", &this->font, Color::Green, Color::Green);
	playerWindow->addButton("quit", Vector2f(centerX -100, 500.f), size, "Отмена", &this->font, Color::Red, Color::Red);

}

//конструктор
MainMenuState::MainMenuState(RenderWindow* window, stack<State*>* states, Event* event, Data * data) : State(window, states)
{
	this->event = event;
	this->gameData = data;

	init();
	initMainWindow();
	initRecords();
	initHelp();
	initPlayerWindow();
	initMusic();
}

//деструктор
MainMenuState::~MainMenuState()
{
	for (auto iter = buttons.begin(); iter != buttons.end(); iter++)
	{
		delete iter->second;
	}
}

//обновление ввода
void MainMenuState::updateInput(const float& dt)
{
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		activeWindow = windows::mainn;
	}

	if (!Mouse::isButtonPressed(Mouse::Left) && pressed)
	{
		pressed = false;
	}
}

void MainMenuState::updateRecords(const float& dt)
{
	if (records->isButtonPressed("quit"))
	{
		activeWindow = windows::mainn;
	}
	if (records->isButtonPressed("delete"))
	{
		records->refresh();
		gameData->deleteRecords();
	}
}

void MainMenuState::updateHelp(const float& dt)
{
	if (help->isButtonPressed("quit"))
	{
		activeWindow = windows::mainn;
		pressed = true;
	}
}

void MainMenuState::updatePlayerWindow(const float& dt)
{
	if (playerWindow->isButtonPressed("quit"))
	{
		playerWindow->clearString();
		activeWindow = windows::mainn;
		pressed = true;
	}
	if (playerWindow->isButtonPressed("ok"))
	{
		if (playerWindow->getString() != "")
		{
			gameData->setNickname(playerWindow->getString());
			playerWindow->clearString();
			activeWindow = windows::mainn;
			pressed = true;
		}
	}
}

//обновление кнопок
void MainMenuState::updateButtons()
{
	for (auto& i : buttons)
	{
		i.second->update(this->mousePosView);
	}

	if (!pressed)
	{
		if (buttons["play"]->isPressed())
		{
			gameData->getMusic()->menuMusic.stop();
			pressed = true;
			states->push(new GameState(window, states, gameData));
		}
		if (buttons["player"]->isPressed())
		{
			activeWindow = windows::player;
		}
		if (buttons["help"]->isPressed())
		{
			activeWindow = windows::help;
		}
		if (buttons["records"]->isPressed())
		{
			activeWindow = windows::records;
			records->refresh();
		}
		if (buttons["exit"]->isPressed())
		{
			gameData->saveRecords();
			gameData->saveSettings();
			gameData->savePlayerInfo();
			endState();
		}
	}
	
}

void MainMenuState::updateToggles()
{
	for (auto& i : toggles)
	{
		i.second->update(this->mousePosView, *event);
	}

	if (toggles["music"]->isToggled())
	{
		gameData->setMusicSettings(true);
		gameData->getMusic()->menuMusic.setVolume(100.f);
	}
	else
	{
		gameData->setMusicSettings(false);
		gameData->getMusic()->menuMusic.setVolume(0.f);
	}

	if (toggles["sfx"]->isToggled())
	{
		gameData->setSfxSettings(true);
	}
	else
	{
		gameData->setSfxSettings(false);

	}
}
//обновление всех компонентов меню
void MainMenuState::update(const float& dt)
{
	stringstream stream;
	stream << "Приветствуем, " << gameData->getPlayerData()->nickname;
	greeting.setString(stream.str());
	stream.str("");

	greeting.setPosition(window->getSize().x / 2 - greeting.getGlobalBounds().width / 2, 180);

	if (gameData->getMusic()->menuMusic.getStatus() == SoundSource::Status::Stopped)
	{
		gameData->getMusic()->menuMusic.play();
	}

	updateInput(dt);

	updateMousePosition();


	switch (activeWindow)
	{
		case windows::records:
		{
			records->update(mousePosView);
			updateRecords(dt);
		} break;
		case windows::help:
		{
			help->update(mousePosView);
			updateHelp(dt);
		} break;
		case windows::player:
		{
			playerWindow->update(mousePosView);
			updatePlayerWindow(dt);
		} break;
		default:
		{
			updateButtons();
			updateToggles();
		} break;
	}
}

//рендер кнопок
void MainMenuState::renderButtons(RenderTarget* target)
{
	for (auto& i : buttons)
	{
		i.second->render(target);
	}

	for (auto& i : toggles)
	{
		i.second->render(target);
	}

	for (auto& i: texts)
	{
		target->draw(*i.second);
	}
}

//рендер всех компонентов меню
void MainMenuState::render(RenderTarget* target)
{
	if (!target)
	{
		target = window;
	}
	
	switch (activeWindow)
	{
		case windows::records:
		{
			records->render(target);
		} break;
		case windows::player:
		{
			window->draw(background);
			this->renderButtons(target);
			window->draw(title);
			window->draw(greeting);
			playerWindow->render(target);
		} break;
		case windows::help:
		{
			help->render(target);
		} break;
		default:
		{
			window->draw(background);
			this->renderButtons(target);
			window->draw(title);
			window->draw(greeting);
		} break;
	}
}