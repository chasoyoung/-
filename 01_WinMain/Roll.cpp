#include "pch.h"
#include "Roll.h"

void Roll::Init(float angle, float speed)
{
	mImage = ImageManager::GetInstance()->FindImage(L"Roll");
	mIname = L"Roll";
	mAngle = angle;
	mSpeed = speed;

	mHp = 10;
	mType = EnemyType::Roll;
	mBulletType = EnemyBulletType::Target;
	mFrameMax = 4;
}

void Roll::Update()
{

	mX += cosf(mAngle) * mSpeed;
	mY -= sinf(mAngle) * mSpeed;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

	UpdateFrame();
	mMoveCount++;
}

void Roll::Render(HDC hdc)
{
	Enemy::Render(hdc);
}
