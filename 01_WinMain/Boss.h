#pragma once
#include "Enemy.h"



class Boss : public Enemy
{
	Point mOripoint;

	float mShotAngle;
	int mRuntime;
	bool turn;
	int mShot;
	int mPhase;
	int mCheck;
	vector<Enemy*> creater;
public:
	void Init();
	void Update();
	void Render(HDC hdc)override;

	void SetFrame();
	void Move(float x = STARTX, float y = 200.f, float speed = 5.f);
	void UpdateMoveCount(int count);
	void ResetMoveCount();
	void CheckPhase();

	void CheckChange();
	
	void Pattern1();
	void Pattern2();
	void Pattern3();
	void Pattern4();
};

