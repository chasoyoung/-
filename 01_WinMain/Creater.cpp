#include "pch.h"
#include "Creater.h"

void Creater::Init(float x, float y, float angle, Enemy* master)
{
	mImage = ImageManager::GetInstance()->FindImage(L"Creater1");
	mIname = L"Creater";

	mMaster = master;
	if (mMaster == NULL)
	{
		mHp = 25;
		mAngle = (Random::GetInstance()->RandomInt(200, 330)) * PI / 180;
	}
	else
	{
		mHp = 200;
		mAngle = angle;
	}
	mSpeed = 5.f;
	mType = EnemyType::Creater;
	mBulletType = EnemyBulletType::Random;
	mFrameMax = 8;

	mCenter = { x, y };
	mRange = 100.f;
}

void Creater::Update()
{
	UpdateCenter();
	if(mMaster != NULL)
	{
		mAngle += 0.055f;

		mX = cosf(mAngle) * (mSpeed + mRange) + mCenter.x;
		mY = -sinf(mAngle) * (mSpeed + mRange) + mCenter.y;
		mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
		UpdateBullet(EnemyBulletType::Target,69);
	}
	else
	{
		//mAngle += 0.055f;
		mX += cosf(mAngle) * 4.f;
		mY -= sinf(mAngle) * 4.f - 1;
		mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
		UpdateBullet(EnemyBulletType::Random, 20);

	}
	UpdateFrame();

	mFiringFrameCount++;
	if (mFiringFrameCount >= 70)
	{
		mFiringFrameCount = 1;
	}
}

void Creater::Render(HDC hdc, bool isAlpha)
{
	Enemy::Render(hdc,true);
}

void Creater::SetMaster(Enemy* master)
{
	mMaster = master;
}
void Creater::UpdateCenter()
{
	if (mMaster == NULL) return;

	mCenter = { mMaster->GetX(), mMaster->GetY() };
}

