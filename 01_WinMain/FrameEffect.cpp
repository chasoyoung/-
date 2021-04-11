#include "pch.h"
#include "FrameEffect.h"
#include "Image.h"

void FrameEffect::Init()
{
	mImage = ImageManager::GetInstance()->FindImage(L"Effect");
	mSizeX = mImage->GetFrameWidth();
	mSizeY = mImage->GetFrameHeight();
	mAngle = 0;
	mSpeed = 10.f;
	mActive = false;

	mFrameCount = 0;
	mFrameIndexX = 0;
	mFrameUpdateCount = 8;
}

void FrameEffect::FrameUpdate()
{
	if (mActive)
	{
		mAngle += 0.3f;
		mX += cos(mAngle) * mSpeed;
		mY -= sin(mAngle) * mSpeed;
		SetRect(mX, mY);

		mFrameCount++;
		if (mFrameCount >= 3)
		{
			mFrameIndexX++;

			if (mFrameIndexX >= 8)
			{
				mActive = false;
				mIsEnd = true;
				mFrameIndexX = 0;
				mAngle = 0;
			}
			mFrameCount = 0;
		}
	}
}

void FrameEffect::Render(HDC hdc)
{
	if(mActive)
		mImage->AlphaFrameRender(hdc, mRect.left, mRect.top, mFrameIndexX, 0, 0.4f);
}

void FrameEffect::SetRect(float x, float y)
{
	mActive = true;
	mX = x;
	mY = y;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}
