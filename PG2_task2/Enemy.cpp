#include "Enemy.h"
#include "Novice.h"

Enemy::Enemy(int speedX)
{
	speedX_ = speedX;
	//radius_ = 20;
}

void Enemy::Update()
{
	if (Alive_)
	{
		posX_ += speedX_;


		if (posX_ - radius_ <= 0 || posX_ + radius_ >= 1280)
		{
			speedX_ *= -1;
		}


		posY_ += speedY_;


		if (posY_ - radius_ <= 0 || posY_ + radius_ >= 720)
		{
			speedY_ *= -1;
		}

	}


	if (Alive_ == 0)
	{
		RespawnTimer--;
	}
	if (RespawnTimer <= 0)
	{
		RespawnTimer = 100;
		Alive_ = true;
	}

}

void Enemy::Draw()
{
	if (Alive_)
	{
		Novice::DrawEllipse
		(
			posX_, posY_, radius_, radius_,
			0.0f, WHITE, kFillModeSolid
		);
	}

}

void Enemy::Init()
{
	Alive_ = true;

	radius_ = rand() % 20 + 20;
	posX_ = rand() % (1280 - radius_ * 2) + radius_;
	posY_ = rand() % (300 - radius_ * 2) + radius_;

	speedX_ = rand() % 4 + 4;
	speedY_ = rand() % 4 + 4;
}

void Enemy::SetAlive(int alive)
{
	Alive_ = alive;
}