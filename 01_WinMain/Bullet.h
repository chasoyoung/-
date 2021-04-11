#pragma once

#include "Unit.h"

class Bullet : public Unit
{

	Target mTarget;
	RECT mRect;
	class Image* mImage;
public:
	void Fire(Image* image, float x, float y,float speed, float angle,int indexX, int indexY,Target target,
		UnitType type);
	void Fire(Image* image, float x, float y, float speed, float angle, int indeX, int indexY, Target target,
		EnemyBulletType type = EnemyBulletType::Null);
	void Update()override;
	void Render(HDC hdc, bool alpha);

	bool GetActive()const { return mActive; }
	RECT GetRect()const { return mRect; }
	Target GetTarget() { return mTarget; }
};

