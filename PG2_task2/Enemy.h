#pragma once

class Enemy
{
public:

	Enemy(int speedX);
	void Update();
	void Draw();
	void Init();

	int GetPosX() { return posX_; };
	int GetPosY() { return posY_; };
	int GetRadius() { return radius_; };

	int GetAlive() { return Alive_; };
	void SetAlive(int alive);

protected:
	int posX_;
	int posY_;
	int radius_;
	int Alive_;
	int speedX_;
	int speedY_;
	int RespawnTimer = 100;

};
