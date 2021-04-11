#include "pch.h"
#include "Boss.h"


void Boss::Init()
{
	mImage = ImageManager::GetInstance()->FindImage(L"Boss");
	mAngle = 0;
	mSpeed = 0;

	mHp = bosshp;
	mType = EnemyType::Boss;
	mBulletType = EnemyBulletType::Random;
	mFrameMax = 4;

	mRuntime = 0;
	mShotCount = 0;
	mMoveCount = 0;
	mFrameCount = 0;
	mOripoint = { STARTX, 200 };

	mShotAngle = 0;
	mPhase = mCheck = 1;

	turn = false;
}

void Boss::Update()
{
	CheckChange();
	CheckPhase();
	if (mRuntime <= 100 || mY != 200 )	//||(mX >= STARTX+0.f && mX < STARTX +1.0f)
	{
		Move();
	}
	else
	{
		switch (mPhase)
		{
		case 1:
			Pattern1();
			break;
		case 2:
			Pattern2();
			break;
		case 3:
			Pattern3();
			break;
		case 4:
			Pattern4();
			break;
		default :
			break;
		}
	}
	SetFrame();
	UpdateFrame(5);
	
	
	mRuntime++;	//페이즈 전환시 초기화

	mFiringFrameCount++;
	if (mFiringFrameCount >= 70)
	{
		mFiringFrameCount = 1;
	}
}

void Boss::Render(HDC hdc)
{
	Enemy::Render(hdc);
}

void Boss::SetFrame()
{
	if (mSpeed == 0)
	{
		mStartFrameX = 9;
		mFrameMax = 10;
	}
	else
	{
		mStartFrameX = 0;
		mFrameMax = 4;
	}
}

//이동
void Boss::Move(float x, float y, float speed)
{
	if (mX != x || mY != y)
	{
		mAngle = Math::GetAngle(mX, mY, x, y);
		mSpeed = speed;

		mX += cosf(mAngle) * mSpeed;
		mY -= sinf(mAngle) * mSpeed;
		mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	}
}
void Boss::UpdateMoveCount(int count)
{
	if (mShotCount == count)
	{
		mMoveCount++;
		mFiringFrameCount = 1;
		mRuntime = 100;
	}
}
void Boss::ResetMoveCount()
{
	mMoveCount = 0;
	mShotCount = 0;
	mFiringFrameCount = 1;

}
//페이즈 체크
void Boss::CheckPhase()
{
	if (mHp < bosshp / 4)
	{
		mPhase = 4;
		return;
	}
	else if (mHp < bosshp / 4 * 2)
	{
		mPhase = 3;
		return;
	}
	else if (mHp < bosshp / 4 * 3)
	{
		mPhase = 2;
		return;
	}
	else if (mHp < bosshp)
	{
		mPhase = 1;
		return;
	}
}

void Boss::CheckChange()
{
	if (mPhase != mCheck)
	{
		mRuntime = 0;
		mCheck = mPhase;
		AllFalse();
		ResetMoveCount();
	}
}

//보스 패턴
void Boss::Pattern1()
{
	switch (mMoveCount)
	{
	case 0:
		if (mX > 200)
		{
			Move(200, mY);
		}
		else
		{
			mSpeed = 0;
			if (mRuntime % 90 == 35)
				Turn();

			TurnFire();
			TurnFire(4.f);

			UpdateMoveCount(6);
		}
		break;
	case 1:
		if (mX < 500)
		{
			Move(500, mY);
		}
		else
		{
			mSpeed = 0;
			if (mRuntime % 90 == 35)
				Turn();

			TurnFire();
			TurnFire(4.f);
			UpdateMoveCount(12);
		}
		break;
	case 2:
		if (mX != mOripoint.x || mY != mOripoint.y)
		{
			Move(mOripoint.x, mOripoint.y);
		}
		else
		{
			mSpeed = 0;
			CenterFire(20,2.f);	//보스 중심발사
			CenterFire(20, 4.f, 25.f);
			UpdateMoveCount(20);
			if (mMoveCount == 3)
				ResetMoveCount();
		}
		break;
	default:
		break;
	}
}
void Boss::Pattern2()
{
	switch (mMoveCount)
	{
	case 0:
		if (mX > 200)
		{
			Move(200, mY);
		}
		else
		{
			mSpeed = 0;
			if (mShotCount % 6 == 0)
				mAngle = PlayerAngle();
			Row3Fire(mAngle, 5.f);
			CenterFire(20, 2.f);
			UpdateMoveCount(18);
		}
		break;
	case 1:
		if (mX < 500)
		{
			Move(500, mY);
		}
		else
		{
			mSpeed = 0;
			if (mShotCount % 6 == 0)
				mAngle = PlayerAngle();
			Row3Fire(mAngle, 5.f);
			CenterFire(20, 2.f);
			UpdateMoveCount(36);
		}
		break;
	case 2:
		if (mX != mOripoint.x || mY != mOripoint.y)
		{
			Move(mOripoint.x, mOripoint.y);
		}
		else
		{
			mSpeed = 0;
			CenterFire(20, 4.f);
			UpdateBullet(EnemyBulletType::Random);
			UpdateMoveCount(41);
			if (mMoveCount == 3)
				ResetMoveCount();
		}
		break;
	default:
		break;
	}
}

void Boss::Pattern3()
{
	if (mX != mOripoint.x || mY != mOripoint.y)
	{
		Move(mOripoint.x, mOripoint.y);
	}
	else
	{
		mSpeed = 0;
		mShotAngle += 0.05f;
		HelixFire(4.5f,mShotAngle);
		HelixFire(4.5f, mShotAngle + PI*2/3);
		HelixFire(4.5f, mShotAngle + PI * 4 / 3);
		if (mShotAngle >= PI2)
			mShotAngle = 0;
	}
}
void Boss::Pattern4()
{
	if (mX>= 500 || mX <= 200)
	{
		turn = !turn;
		mRuntime = 200;
	}
	if(turn)
		Move(200, mY, 2.5f);
	else
		Move(500, mY, 2.5f);

	mShotAngle -= 0.05f;
	HelixFire(7.f, mShotAngle);
	HelixFire(3.5f, -mShotAngle + PI * 2 / 3);
	HelixFire(4.5f, mShotAngle + PI * 4 / 3);
	DivideFire();
	if (mShotCount == 5)
	{
		Divide();
		mShotCount = 0;
	}

	if (mShotAngle >= PI2)
		mShotAngle = 0;
}