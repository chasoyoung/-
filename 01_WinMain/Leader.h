#pragma once
#include "Enemy.h"
class Leader : public Enemy
{
	float turnpoint;
	int mRuntime;
	float mSp;
	bool turn;
public:
	void Init(float x);
	void Update()override;
	void Render(HDC hdc)override;
};

