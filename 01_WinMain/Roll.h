#pragma once
#include "Enemy.h"
class Roll : public Enemy
{
public:
	void Init(float angle, float speed);
	void Update()override;
	void Render(HDC hdc)override;
};

