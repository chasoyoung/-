#include "pch.h"
#include "Nomal.h"

void Nomal::Init(float x, float y)
{
	mImage = ImageManager::GetInstance()->FindImage(L"Nomal");
	mX = x;
	mY = y;
	if (mX < STARTX)
		mAngle = PI2 - (PI / 4.f);
	else if(mX > STARTX)
		mAngle = PI + (PI / 4.f);
	mSpeed = 5.f;

	mHp = 5;
	mType = EnemyType::Normal;
	mBulletType = EnemyBulletType::Target;
	mIndexX = 0;
	mFrameMax = 4;
}

void Nomal::Update()
{
	mX += cosf(mAngle) * mSpeed;
	mY -= sinf(mAngle) * mSpeed;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	if (mY > WINSIZEY / 3)
		mAngle = PI2 - mAngle;

	UpdateBullet(EnemyBulletType::Target, 50);
	mFiringFrameCount++;
	if (mFiringFrameCount >= 100)
		mFiringFrameCount = 1;
	UpdateFrame();
}

void Nomal::Render(HDC hdc)
{
	Enemy::Render(hdc);
}
