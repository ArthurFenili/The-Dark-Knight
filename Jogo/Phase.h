#pragma once

#include "EntitiesList.h"
#include "PlatformList.h"
#include "Enemy.h"
#include "EnemyProjectile.h"

class Phase
{
private:
	GraphicsManager* graphicsManager;
	EntitiesList entitiesList;
	PlatformList platformList;

public:
	Phase(GraphicsManager* graphicsManager);
	Phase();
	~Phase();

	void setPlatform(sf::Vector2f position, std::string pathToTexture, std::string textureName, sf::Vector2f bodySize);
	void setEnemy(sf::Vector2f position, std::string pathToTexture, std::string textureName, sf::Vector2f bodySize, float* dt, float spriteScale, float speed, Player* player);
	void setEnemy2(sf::Vector2f position, std::string pathToTexture, std::string textureName, sf::Vector2f bodySize, float* dt, float spriteScale, float speed, Player* player);

	void addEntity(Entity* entity) { this->entitiesList.addEntity(entity); }

	void update();

	void render();

	EntitiesList* getEntityList() { return &this->entitiesList; }
	PlatformList* getPlatformList() { return &this->platformList; }
};
