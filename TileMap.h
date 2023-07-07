#pragma once

#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <vector>
#include <cmath>
#include <fstream>

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"
#include "SFML/System.hpp"

#include "Tile.h"
#include "DataPaths.h"
#include "Enemy.h"
#include "ShootComponent.h"
using namespace std;
using namespace sf;

#define SPIKES IntRect(64,192, 16, 16)

class TileMap
{
private:
	Texture* texture;// текстура с тайлами

	float tileSize;
	unsigned gridSize; // размер сетки
	unsigned layers; // количество слоёв
	Vector2u maxSize; // максимальный размер
	Vector2u maxSizeWorld; // максимальный размер
	float scale; //масштаб тайлов

	vector< vector< vector<Tile*>>> tileMap; // тайловая карта
	map <int, Vector2u> tileTypes; // типы тайлов

	int fromX;
	int toX;
	int fromY;
	int toY;

	int collisionLayer;
	int spikeLayer;
public:
	//конструктор / деструктор
	TileMap(unsigned gridSize, unsigned width, unsigned height, float scale, int layers, Texture* texture);
	~TileMap();

	//геттеры
	const Vector2u& getSize();

	//функции

	//обновление
	void updateTileCollision(Entity * entity, const float& dt);
	void updateEnemyTileCollision(Enemy* entity, const float& dt);
	void updateTileCollision(Fireball* fireball, const float& dt);
	void updateCollisionBounds(Entity * entity);
	void update(const float& dt);

	Vector2f findTileX(Vector2i TilePos , int left, int velocity, float width);
	Vector2f findTileY(Vector2i TilePos, int left, int velocity, float height);
	bool isFreeTile(float x, float y);

	//рендер
	void render(RenderTarget& target);

	//функции загрузки
	void loadFromFile(string filename, unsigned layer);
	void loadTileTypes(string filename);
};