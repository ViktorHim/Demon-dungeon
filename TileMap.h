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
	Texture* texture;// �������� � �������

	float tileSize;
	unsigned gridSize; // ������ �����
	unsigned layers; // ���������� ����
	Vector2u maxSize; // ������������ ������
	Vector2u maxSizeWorld; // ������������ ������
	float scale; //������� ������

	vector< vector< vector<Tile*>>> tileMap; // �������� �����
	map <int, Vector2u> tileTypes; // ���� ������

	int fromX;
	int toX;
	int fromY;
	int toY;

	int collisionLayer;
	int spikeLayer;
public:
	//����������� / ����������
	TileMap(unsigned gridSize, unsigned width, unsigned height, float scale, int layers, Texture* texture);
	~TileMap();

	//�������
	const Vector2u& getSize();

	//�������

	//����������
	void updateTileCollision(Entity * entity, const float& dt);
	void updateEnemyTileCollision(Enemy* entity, const float& dt);
	void updateTileCollision(Fireball* fireball, const float& dt);
	void updateCollisionBounds(Entity * entity);
	void update(const float& dt);

	Vector2f findTileX(Vector2i TilePos , int left, int velocity, float width);
	Vector2f findTileY(Vector2i TilePos, int left, int velocity, float height);
	bool isFreeTile(float x, float y);

	//������
	void render(RenderTarget& target);

	//������� ��������
	void loadFromFile(string filename, unsigned layer);
	void loadTileTypes(string filename);
};