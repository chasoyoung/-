#pragma once
#include "Enemy.h"
class Creater : public Enemy
{
	Enemy* mMaster;
	float mRange;
	//RECT mCenter;
	Point mCenter;

	float mTo;
public:
	void Init(float x, float y, float angle, Enemy* master = NULL);
	void Update()override;
	void Render(HDC hdc, bool isAlpha);

	void SetMaster(Enemy* master);
	void UpdateCenter();
	
};

