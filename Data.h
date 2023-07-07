#pragma once
#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <cmath>
#include <fstream>


#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"
#include "SFML/System.hpp"

using namespace std;
using namespace sf;
#include "DataPaths.h"
#include <algorithm>

enum sounds
{
	fireball,
	damage,
	potion
};

struct PlayerData
{
	string nickname;//им€ игрока

	float cooldown;//врем€ неу€звимости
	float velocity; // скорость
	float maxHealth;//максимальное здоровье
	float maxMana;//максимальна€ мана
	float damage;//урон
};

struct Settings
{
	bool music;//музыка
	bool sfx;//эффекты
};

struct MusicData
{
	Music inGameMusic;//музыка в игре
	Music menuMusic;//музыка в меню
};

struct sfxData//звуки
{
	map<int, SoundBuffer> buffers;
	map<int, Sound> sounds;
};


class Data
{
private:
	PlayerData playerData;
	Settings settings;
	MusicData music;
	sfxData sfx;
	vector<pair<int, string>> scores;

	void initPlayerData();
	void initSettings();
	void initScores();
	void initMusic();
	void initSfx();
public:
	Data();
	~Data();

	void saveSettings();
	void saveRecords();
	void savePlayerInfo();

	PlayerData* getPlayerData();
	Settings* getSettings();
	vector<pair<int, string>> * getBestScores();
	MusicData* getMusic();
	sfxData*  getSfx();

	void setMusicSettings(bool music);
	void setSfxSettings(bool sfx);
	void setNickname(string nick);

	void addScore(int score);
	void deleteRecords();
};