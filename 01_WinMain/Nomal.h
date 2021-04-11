#pragma once
#include "Enemy.h"
class Nomal : public Enemy
{
public:
	void Init(float x, float y);
	void Update()override;
	void Render(HDC hdc)override;
};

