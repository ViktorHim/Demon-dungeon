#include "Data.h"

void Data::initPlayerData()
{
	ifstream in;

	in.open(PLAYER_INFO);

	if (in.is_open())
	{
		in >> playerData.nickname;

		in >> playerData.cooldown;
		in >> playerData.velocity;
		in >> playerData.maxHealth;
		in >> playerData.maxMana;
		in >> playerData.damage;

		in.close();
	}
	else
	{
		playerData.nickname = "player";

		playerData.cooldown = 0.5f;
		playerData.velocity = 300.f;
		playerData.maxHealth = 100.f;
		playerData.maxMana = 200.f;
		playerData.damage = 10.f;
	}
}

void Data::initSettings()
{
	ifstream in;

	in.open(SETTINGS);

	if (in.is_open())
	{
		in >> settings.music;
		in >> settings.sfx;

		in.close();

	}
	else
	{
		settings.music = true;
		settings.sfx = true;
	}
}

void Data::initScores()
{
	ifstream in;

	in.open(SCORES);


	int a;
	int score;
	string nickname;
	in >> a;
	if (a == 0)
	{
		return;
	}
	int k = 0;
	while (!in.eof() && k < a)
	{
		in >> score;
		in >> nickname;
		scores.push_back(pair<int, string>(score, nickname));
		k++;
	}
	
	if (!scores.empty())
	{
		std::sort(scores.begin(), scores.end(), greater<pair<int, string>>());
	}

	in.close();
}

void Data::initMusic()
{
	music.inGameMusic.openFromFile(IN_GAME_MUSIC_1);
	music.menuMusic.openFromFile(MENU_MUSIC);
}

void Data::initSfx()
{
	sfx.buffers[fireball].loadFromFile(FIREBALL_SOUND);
	sfx.sounds[fireball].setBuffer(sfx.buffers[fireball]);
	sfx.buffers[damage].loadFromFile(ENEMY_DAMAGE_SOUND);
	sfx.sounds[damage].setBuffer(sfx.buffers[damage]);
	sfx.buffers[potion].loadFromFile(POTION_SOUND);
	sfx.sounds[potion].setBuffer(sfx.buffers[potion]);
}

Data::Data()
{
	initPlayerData();
	initSettings();
	initScores();
	initSfx();
	initMusic();
}

Data::~Data()
{
}

void Data::saveSettings()
{
	ofstream out;

	out.open(SETTINGS, ios::out);

	out << settings.music << endl;
	out << settings.sfx << endl;

	out.close();

}

void Data::saveRecords()
{
	ofstream out;

	out.open(SCORES, ios::out);

	if (!scores.empty())
	{
		out << scores.size() << endl;
		for (auto i : scores)
		{
			out << i.first << endl;
			out << i.second << endl;
		}
	}
	else
	{
		out << 0;
	}

}

void Data::savePlayerInfo()
{
	ofstream out;

	out.open(PLAYER_INFO, ios::out);

	out << playerData.nickname << endl;

	out << playerData.cooldown << endl;
	out << playerData.velocity << endl;
	out << playerData.maxHealth << endl;
	out << playerData.maxMana << endl;
	out << playerData.damage << endl;

	out.close();
}

PlayerData* Data::getPlayerData()
{
	return &playerData;
}

Settings * Data::getSettings()
{
	return &settings;
}

vector<pair<int, string>>* Data::getBestScores()
{
	return &scores;
}

MusicData* Data::getMusic()
{
	return &music;
}

sfxData* Data::getSfx()
{
	return &sfx;
}

void Data::setMusicSettings(bool music)
{
	settings.music = music;
}

void Data::setSfxSettings(bool sfx)
{
	settings.sfx = sfx;
}

void Data::setNickname(string nick)
{
	playerData.nickname = nick;
}

void Data::addScore(int score)
{
	pair<int, string> a;
	a.first = score;
	a.second = playerData.nickname;

	scores.push_back(a);
	std::sort(scores.begin(), scores.end(), greater<pair<int, string>>());

	if (scores.size() > 10)
	{
		scores.pop_back();
	}
}

void Data::deleteRecords()
{
	scores.clear();
}


