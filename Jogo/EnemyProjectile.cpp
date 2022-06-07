#include "EnemyProjectile.h"

const float WIDTH_AUX = 2.f;
const float HEIGHT_AUX = 2.6f;

EnemyProjectile::EnemyProjectile(GraphicsManager* graphicsManager, sf::Vector2f position, std::string pathToTexture, std::string textureName, sf::Vector2f bodySize, 
	float* dt, float spriteScale, float speed):
	Enemy(graphicsManager, position, pathToTexture, textureName, bodySize, dt, spriteScale, speed)
{
	this->speed = speed;
	this->player1 = nullptr;

	this->animation = new AnimationManager();
	this->animation->setImageCount(sf::Vector2u(8, 1));
	this->animation->setSwitchTime(0.3f);
	this->animation->setUVRect(this->texture);

	this->sprite.setTexture(*this->texture);

	this->body.setFillColor(sf::Color(0, 0, 0, 0));
	this->body.setOutlineColor(sf::Color::Red);
	this->body.setOutlineThickness(1.f);

	this->attacking = false;
	shootTimer = 0;
	projectile = new Projectile();
	projectile->setUser(this);

}

EnemyProjectile::EnemyProjectile()
{
	this->animation = nullptr;
	this->player1 = nullptr;
	this->speed = 0.f;
}

EnemyProjectile::~EnemyProjectile()
{
	delete this->animation;
	delete this->projectile;
}

void EnemyProjectile::update() {
	this->updateMovement();
	this->updatePosition();
	this->updateAttack();
	//this->updateAnimation();
}

void EnemyProjectile::updateMovement() {
	this->velocity.y += 2.f * this->gravity * (*this->dt);

	if (this->player1->getPosition().x > this->getPosition().x) {
		this->velocity.x = 1.f * this->speed;
		//this->body.move(this->velocity * (*this->dt));
		//this->facingRight = true;
	}
	if (this->player1->getPosition().x < this->getPosition().x) {
		this->velocity.x = -1.f * this->speed;
		//this->body.move(this->velocity * (*this->dt));
		//this->facingRight = false;
	}

	this->body.move(this->velocity * (*this->dt));

	this->position = this->body.getPosition();
	this->sprite.setPosition(this->position);
}

void EnemyProjectile::updateAttack()
{
	if (shootTimer < 2000)
		shootTimer++;

	if (shootTimer >= 2000) {
		projectile->createProjectile();
		shootTimer = 0;
	}

	for (int i = 0; i < projectile->getVectorSize(); i++) {
		if (this->player1->getPosition().x < this->getPosition().x)
			projectile->moveProjectile(i, -1.f);
		else if (this->player1->getPosition().x > this->getPosition().x)
			projectile->moveProjectile(i, 1.f);
		projectile->verifyErase(i);
	}
}

void EnemyProjectile::updatePosition() {
	this->position = this->body.getPosition();

	if (this->facingRight)
		this->sprite.setPosition(sf::Vector2f(this->position.x + this->body.getSize().x * (WIDTH_AUX / this->spriteScale), this->position.y + this->body.getSize().y * (HEIGHT_AUX / this->spriteScale)));
	else
		this->sprite.setPosition(sf::Vector2f(this->position.x - this->body.getSize().x * (WIDTH_AUX / this->spriteScale), this->position.y + this->body.getSize().y * (HEIGHT_AUX / this->spriteScale)));
}

void EnemyProjectile::updateAnimation()
{
	this->animation->update(0, *this->dt);
	this->sprite.setTextureRect(this->animation->getUVRect());
}