#include "pch.h"
#include "Bullet.h"

#include "Image.h"

void Bullet::Fire(Image* image, float x, float y,
	float speed, float angle,
	int indexX, int indexY,
	Target target, UnitType type)//添発持失
{
	mIndexX = indexX;
	mIndexY = indexY;
	mType = type;
	mTarget = target;
	mImage = image;

	mSizeX = mImage->GetFrameWidth();
	mSizeY = mImage->GetFrameHeight();

	mX = x;
	mY = y;
	mSpeed = mOriginSpeed = speed;
	mAngle = angle;
	mActive = true;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}
void Bullet::Fire(Image * image, float x, float y, 
					float speed, float angle, 
					int indexX, int indexY, 
					Target target, EnemyBulletType type)//添発持失
{
	mIndexX = indexX;
	mIndexY = indexY;
	mBType = type;
	mTarget = target;
	mImage = image;

	mSizeX = mImage->GetFrameWidth();
	mSizeY = mImage->GetFrameHeight();

	mX = x;
	mY = y;
	mSpeed = mOriginSpeed = speed;
	mAngle = angle;
	mActive = true;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void Bullet::Update()
{
	if (mActive)
	{
		mX += cosf(mAngle) * mSpeed;
		mY += -sinf(mAngle) * mSpeed;
		mRect= RectMakeCenter(mX, mY, mSizeX, mSizeY);
	}

	if (mX < PLAYLEFT) mActive = false;
	else if (mX > PLAYRIGHT) mActive = false;
	else if (mY < PLAYTOP) mActive = false;
	else if (mY > PLAYBOTTOM) mActive = false;
}

void Bullet::Render(HDC hdc, bool alpha)
{
	if(mActive == true)
	{
		if(alpha == true)
			mImage->AlphaFrameRender(hdc, mRect.left, mRect.top, mIndexX, mIndexY,0.5f);
		else if (alpha == false)
		{
			mImage->FrameRender(hdc, mRect.left, mRect.top, mIndexX, mIndexY);
		}
	}
}
