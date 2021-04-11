#include "pch.h"
#include "Leader.h"

void Leader::Init(float x)
{
	mImage = ImageManager::GetInstance()->FindImage(L"Leader");

	mX = x;
	mY = 0;

	if (mX < STARTX)
	{
		mSp = 1.5f;
		turnpoint = PLAYRIGHT + (x - STARTX);
	}
	else if (mX > STARTX)
	{
		mSp = -1.5f;
		turnpoint = PLAYLEFT + (x - STARTX);
	}
	else if (mX == STARTX)
	{
		mSp = 0;
	}
	mSpeed = 5.f;

	mHp = 30;
	mRuntime = 0;
	mSpeed = 3.f;
	turn = false;
}

void Leader::Update()
{
	if (turn)
		mY -= mSpeed;
	else if (mRuntime >= 120 && !turn)
		mX += mSp;
	else if (mRuntime <= 80 && !turn)
		mY += mSpeed;

	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);


	if (mShotCount == 0)
		mAngle = PlayerAngle();
	Row3Fire(mAngle);

	UpdateBullet(EnemyBulletType::Target, 50);
	mFiringFrameCount++;
	if (mFiringFrameCount >= 100)
	{
		mFiringFrameCount = 1;
		mShotCount = 0;
	}
	mRuntime++;
	if (mSp > 0)
	{
		if (mX > turnpoint)
		{
			turn = true;
		}
	}else if (mSp < 0)
	{
		if (mX < turnpoint)
		{
			turn = true;
		}
	}
	else if (mSp == 0)
	{
		if (mRuntime == 300)
		{
			turn = true;
		}
	}

}

void Leader::Render(HDC hdc)
{
	Enemy::Render(hdc);

}
