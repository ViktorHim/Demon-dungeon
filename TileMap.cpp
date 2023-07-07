#include "TileMap.h"
//конструктор
TileMap::TileMap(unsigned gridSize, unsigned width, unsigned height, float scale, int layers, Texture* texture)
{
	this->gridSize = gridSize;
	this->maxSize = Vector2u(width, height);
	this->layers = layers;
	this->texture = texture;
	this->scale = scale;

	this->tileSize = this->gridSize * this->scale;

	this->maxSizeWorld.x = this->tileSize * this->maxSize.x;
	this->maxSizeWorld.y = this->tileSize * this->maxSize.y;

	this->fromX = 0;
	this->toX = 0;
	this->fromY = 0;
	this->toY = 0;

	this->collisionLayer = 1;
	this->spikeLayer = 2;

	this->tileMap.resize(this->maxSize.x, vector<vector<Tile*>>());
	for (int x = 0; x < this->maxSize.x; x++)
	{
		for (int y = 0; y < this->maxSize.y; y++)
		{
			this->tileMap[x].resize(this->maxSize.y, vector<Tile*>());

			for (int z = 0; z < layers; z++)
			{
				this->tileMap[x][y].resize(this->layers, NULL);
			}
		}
	}

	this->loadTileTypes(TILE_TYPES);
}

//деструктор
TileMap::~TileMap()
{
	for (int x = 0; x < this->maxSize.x; x++)
	{
		for (int y = 0; y < this->maxSize.y; y++)
		{
			for (int z = 0; z < layers; z++)
			{
				delete this->tileMap[x][y][z];
			}
		}
	}
}

//геттер размера карты
const Vector2u& TileMap::getSize()
{
	return this->maxSizeWorld;
}

//загрузка типов тайлов
void TileMap::loadTileTypes(string filename)
{
	ifstream in;
	int key;
	int count;
	Vector2u pos;


	in.open(filename);

	if (in.is_open())
	{
		in >> count;

		for (int i = 0; i < count; i++)
		{
			in >> key;
			in >> pos.x;
			in >> pos.y;

			this->tileTypes[key] = pos;
		}
	}
	else
	{
		cout << "ERROR LOADIND TYPES OF TILES FROM: " << filename << endl;
	}
}


//загрузка сло€ карты из файла
void TileMap::loadFromFile(string filename, unsigned layer)
{
	int type;
	int cordX;
	int cordY;

	ifstream in;
	in.open(filename);

	if (in.is_open())
	{
		for (int x = 0; x < this->maxSize.x; x++)
		{
			for (int y = 0; y < this->maxSize.y; y++)
			{
					in >> type;
					cordX = this->scale * this->gridSize * x;
					cordY = this->scale * this->gridSize * y;
					if (type)
					{
						tileMap[x][y][layer] = new Tile(tileTypes[type].x, tileTypes[type].y, this->gridSize, cordX, cordY,this->scale, this->texture);
						switch (layer)
						{
							case 1:
							{
								tileMap[x][y][layer]->setTag("Wall");
							} break;
							case 2:
							{
								tileMap[x][y][layer]->setAnimation(4, 50.f);
								tileMap[x][y][layer]->setTag("Spikes");
							} break;
						}
					}
			}
		}
	}
	else
	{
		cout << "ERROR LOADIND TILES FROM: " << filename << endl;
	}
}

void TileMap::updateTileCollision(Entity* entity, const float& dt)
{

	Vector2f currPos = entity->getPosition();

	this->fromX = entity->getGridPosition(this->tileSize).x - 1;
	if (this->fromX < 0)
	{
		this->fromX = 0;
	}
	else if (this->fromX > this->maxSize.x)
	{
		this->fromX = this->maxSize.x;
	}

	this->toX = entity->getGridPosition(this->tileSize).x + 3;
	if (this->toX < 0)
	{
		this->toX = 0;
	}
	else if (this->toX > this->maxSize.x)
	{
		this->toX = this->maxSize.x;
	}

	this->fromY = entity->getGridPosition(this->tileSize).y - 1;
	if (this->fromY < 0)
	{
		this->fromY = 0;
	}
	else if (this->fromY > this->maxSize.y)
	{
		this->fromY = this->maxSize.y;
	}

	this->toY = entity->getGridPosition(this->tileSize).y + 3;
	if (this->toY < 0)
	{
		this->toY = 0;
	}
	else if (this->toX > this->maxSize.y)
	{
		this->toY = this->maxSize.y;
	}

	FloatRect playerBounds;
	FloatRect wallBounds;

	for (int x = this->fromX; x < this->toX; x++)
	{
		for (int y = this->fromY; y < this->toY; y++)
		{
			playerBounds = entity->getGlobalBounds();
			if (this->tileMap[x][y][this->collisionLayer])
			{	
				wallBounds = this->tileMap[x][y][this->collisionLayer]->getGlobalBounds();
				
				if (this->tileMap[x][y][this->collisionLayer]->isCollision(playerBounds))
				{
					//столкновение снизу
					if (playerBounds.top < wallBounds.top
						&& playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height
						&& playerBounds.left < wallBounds.left + wallBounds.width
						&& playerBounds.left + playerBounds.width > wallBounds.left
						)
					{
						entity->setPosition(playerBounds.left, wallBounds.top - playerBounds.height);
					}

					//столкновение сверху
					else if (playerBounds.top > wallBounds.top
						&& playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height
						&& playerBounds.left < wallBounds.left + wallBounds.width
						&& playerBounds.left + playerBounds.width > wallBounds.left
						)
					{
						entity->setPosition(playerBounds.left, wallBounds.top + wallBounds.height);

					}

					//столкновение справа
					if (playerBounds.left  < wallBounds.left 
						&& playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width
						&& playerBounds.top < wallBounds.top + wallBounds.height - 10
						&& playerBounds.top + playerBounds.height > wallBounds.top + 10
						)
					{
						entity->setPosition(wallBounds.left - playerBounds.width, playerBounds.top);

					}

					//столкновение слева
					else if (playerBounds.left > wallBounds.left 
						&& playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width
						&& playerBounds.top  < wallBounds.top + wallBounds.height - 10
						&& playerBounds.top + playerBounds.height > wallBounds.top + 10
						)
					{
						entity->setPosition(wallBounds.left + wallBounds.width, playerBounds.top);

					}
				}
			}

			if (this->tileMap[x][y][this->spikeLayer])
			{
				if (this->tileMap[x][y][this->spikeLayer]->isCollision(playerBounds) && this->tileMap[x][y][this->spikeLayer]->getSpriteRect() == SPIKES)
				{
					entity->setDamage(5.f);
				}
			}
			
		}
	}
}

void TileMap::updateEnemyTileCollision(Enemy* entity, const float& dt)
{
	Vector2f currPos = entity->getPosition();

	this->fromX = entity->getGridPosition(this->tileSize).x - 1;
	if (this->fromX < 0)
	{
		this->fromX = 0;
	}
	else if (this->fromX > this->maxSize.x)
	{
		this->fromX = this->maxSize.x;
	}

	this->toX = entity->getGridPosition(this->tileSize).x + 3;
	if (this->toX < 0)
	{
		this->toX = 0;
	}
	else if (this->toX > this->maxSize.x)
	{
		this->toX = this->maxSize.x;
	}

	this->fromY = entity->getGridPosition(this->tileSize).y - 1;
	if (this->fromY < 0)
	{
		this->fromY = 0;
	}
	else if (this->fromY > this->maxSize.y)
	{
		this->fromY = this->maxSize.y;
	}

	this->toY = entity->getGridPosition(this->tileSize).y + 3;
	if (this->toY < 0)
	{
		this->toY = 0;
	}
	else if (this->toX > this->maxSize.y)
	{
		this->toY = this->maxSize.y;
	}

	FloatRect playerBounds;
	FloatRect wallBounds;

	for (int x = this->fromX; x < this->toX; x++)
	{
		for (int y = this->fromY; y < this->toY; y++)
		{
			playerBounds = entity->getGlobalBounds();
			
			if (this->tileMap[x][y][this->collisionLayer])
			{
				wallBounds = this->tileMap[x][y][this->collisionLayer]->getGlobalBounds();
				if (this->tileMap[x][y][this->collisionLayer]->isCollision(playerBounds))
				{
					//столкновение справа
					if (playerBounds.left < wallBounds.left
						&& playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width
						&& playerBounds.top < wallBounds.top + wallBounds.height
						&& playerBounds.top + playerBounds.height > wallBounds.top
						)
					{
						if (entity->getFollow() && entity->getVelocity().x == 1)
						{
							entity->setTarget(Vector2f(findTileY(Vector2i(x, y), -1, entity->getVelocity().y, playerBounds.height / 2)));
							entity->setFollow(false);
						}
						
					}
					//столкновение слева
					else if (playerBounds.left > wallBounds.left
						&& playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width
						&& playerBounds.top  < wallBounds.top + wallBounds.height
						&& playerBounds.top + playerBounds.height > wallBounds.top
						)
					{						
						if (entity->getFollow() && entity->getVelocity().x == -1)
						{
							entity->setTarget(Vector2f(findTileY(Vector2i(x, y), 1, entity->getVelocity().y, playerBounds.height / 2)));
							entity->setFollow(false);
						}
					}
				}

				//столкновение снизу
				if (playerBounds.top  < wallBounds.top
					&& playerBounds.top + playerBounds.height  < wallBounds.top + wallBounds.height
					&& playerBounds.left < wallBounds.left + wallBounds.width
					&& playerBounds.left + playerBounds.width > wallBounds.left
					)
				{
					if (entity->getFollow() && entity->getVelocity().y == 1)
					{
						entity->setTarget(Vector2f(findTileX(Vector2i(x, y), -1, entity->getVelocity().x, playerBounds.width / 2)));
						entity->setFollow(false);
					}

				}
				//столкновение сверху
				else if (playerBounds.top > wallBounds.top
					&& playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height
					&& playerBounds.left < wallBounds.left + wallBounds.width
					&& playerBounds.left + playerBounds.width > wallBounds.left
					)
				{
					if (entity->getFollow() && entity->getVelocity().y == -1)
					{
						entity->setTarget(Vector2f(findTileX(Vector2i(x, y), 1, entity->getVelocity().x, playerBounds.width / 2)));
						entity->setFollow(false);
					}
				}
			}

			/*if (this->tileMap[x][y][this->spikeLayer])
			{
				if (this->tileMap[x][y][this->spikeLayer]->isCollision(playerBounds) && this->tileMap[x][y][this->spikeLayer]->getSpriteRect() == SPIKES)
				{
					entity->setDamage(5.f);
				}
			}*/

		}
	}
}



void TileMap::updateTileCollision(Fireball* fireball, const float& dt)
{
	Vector2f currPos = fireball->getPosition();

	this->fromX = fireball->getGridPosition(this->tileSize).x - 1;
	if (this->fromX < 0)
	{
		this->fromX = 0;
	}
	else if (this->fromX > this->maxSize.x)
	{
		this->fromX = this->maxSize.x;
	}

	this->toX = fireball->getGridPosition(this->tileSize).x + 3;
	if (this->toX < 0)
	{
		this->toX = 0;
	}
	else if (this->toX > this->maxSize.x)
	{
		this->toX = this->maxSize.x;
	}

	this->fromY = fireball->getGridPosition(this->tileSize).y - 1;
	if (this->fromY < 0)
	{
		this->fromY = 0;
	}
	else if (this->fromY > this->maxSize.y)
	{
		this->fromY = this->maxSize.y;
	}

	this->toY = fireball->getGridPosition(this->tileSize).y + 3;
	if (this->toY < 0)
	{
		this->toY = 0;
	}
	else if (this->toY > this->maxSize.y)
	{
		this->toY = this->maxSize.y;
	}

	FloatRect bulletBounds;
	FloatRect wallBounds;

	for (int x = this->fromX; x < this->toX; x++)
	{
		for (int y = this->fromY; y < this->toY; y++)
		{
			bulletBounds = *fireball->getGlobalBounds();
			if (this->tileMap[x][y][this->collisionLayer])
			{
				wallBounds = this->tileMap[x][y][this->collisionLayer]->getGlobalBounds();

				if (this->tileMap[x][y][this->collisionLayer]->isCollision(bulletBounds))
				{
					fireball->isEnd = true;
				}
			}
		}
	}
}

void TileMap::updateCollisionBounds(Entity* entity)
{
	if (entity->getPosition().x  - this->tileSize < 0.f)
	{
		entity->setPosition(0.f + this->tileSize, entity->getPosition().y);
	}
	else if (entity->getPosition().x + this->tileSize > this->maxSizeWorld.x)
	{
		entity->setPosition(this->maxSizeWorld.x - this->tileSize, entity->getPosition().y);
	}
	if (entity->getPosition().y - this->tileSize < 0.f)
	{
		entity->setPosition(entity->getPosition().x, 0.f + this->tileSize);
	}
	else if (entity->getPosition().y + entity->getGlobalBounds().height + this->tileSize > this->maxSizeWorld.y)
	{
		entity->setPosition(entity->getPosition().x, this->maxSizeWorld.y - entity->getGlobalBounds().height - this->tileSize);
	}
}

//обновление тайлов с анимацией
void TileMap::update(const float& dt)
{
	for (int x = 0; x < this->maxSize.x; x++)
	{
		for (int y = 0; y < this->maxSize.y; y++)
		{
			this->tileMap[x][y][2]->update(dt);
		}
	}
}

Vector2f TileMap::findTileX(Vector2i TilePos, int left, int velocity, float width)
{
	for (int i = 0; i < 10; i++)
	{
		if (TilePos.x + i * velocity < maxSize.x) 
		{
			if (!tileMap[TilePos.x + i * velocity][TilePos.y][collisionLayer])
			{
				return Vector2f((TilePos.x + i * velocity) * 48 + width * velocity, (TilePos.y + left) * 48);
			}	
		}
		else
		{
			if (!tileMap[TilePos.x][TilePos.y][collisionLayer])
			{
				return Vector2f((TilePos.x) * 48 + width * velocity, (TilePos.y + left) * 48);
			}
		}
	}

	return Vector2f();
}
Vector2f TileMap::findTileY(Vector2i TilePos, int left, int velocity, float height)
{
	for (int i = 0; i < 10; i++)
	{
		if (TilePos.y + i * velocity < maxSize.y)
		{
			if (!tileMap[TilePos.x][TilePos.y + i * velocity][collisionLayer])
			{
				return Vector2f((TilePos.x + left) * 48, (TilePos.y + i * velocity) * 48 + height * velocity);
			}
		}
		else
		{
			if (!tileMap[TilePos.x][TilePos.y][collisionLayer])
			{
				return Vector2f((TilePos.x + left) * 48, (TilePos.y) * 48 + height * velocity);
			}
		}
		
	}
	return Vector2f();
}

bool TileMap::isFreeTile(float x, float y)
{
	if (tileMap[x][y][collisionLayer])
	{
		return false;
	}

	return true;
}


//рендер тайлов
void TileMap::render(RenderTarget& target)
{
	for (auto& x : this->tileMap)
	{
		for (auto& y : x)
		{
			for (auto& z : y)
			{
				z->render(target);
			}
		}
	}
}