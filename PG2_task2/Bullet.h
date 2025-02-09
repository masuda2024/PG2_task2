#pragma once

class Bullet
{
public:
	Bullet();
	void Update();
	void Draw();

	int GetPosX() { return posX_; };
	int GetPosY() { return posY_; };
	void SetPosition(int x, int y);

	int GetRadius() { return radius_; };

	int GetIsShot() { return isShot_; };
	void SetIsShot(int isShot);

protected:

	int posX_;
	int posY_;
	int radius_;
	int speedX_;
	int speedY_;
	int isShot_;

};


