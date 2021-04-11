#include "pch.h"
#include "Enemy.h"

#include "Image.h"
#include "Bullet.h"
#include "Player.h"
#include "BulletManager.h"
#include "EnemyKind.h"
//생성관련
void Enemy::Init( int x, int y, int startX, int startY)
{

	mX = x;
	mY = y;
	mSizeX = mImage->GetFrameWidth();
	mSizeY = mImage->GetFrameHeight();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mOriginSpeed = mSpeed;
	mActive = true;

	mIndexX = mStartFrameX = startX;
	mIndexY = mStartFrameY = startY;

	mShotCount = 0;
	mFrameCount = 0;
	mMoveCount = 0;
	mFiringFrameCount = 0;
}

//
void Enemy::Release()
{

}

void Enemy::Update()
{
	UpdateMove();
	UpdateFrame();
	if (CheckRange())	//Acitve가 True일때만
	{
		UpdateBullet(EnemyBulletType::Target);
	}
	mFiringFrameCount++;
	if (mFiringFrameCount >= 90)
		mFiringFrameCount = 1;
}

void Enemy::Render(HDC hdc, bool isAlpha)
{
	if (isAlpha)
	{
		mImage->AlphaFrameRender(hdc, mRect.left, mRect.top, mIndexX, mIndexY, 0.5f);
	}else if(!isAlpha)
		mImage->FrameRender(hdc, mRect.left, mRect.top, mIndexX, mIndexY);
}


void Enemy::UpdateMove()
{
	mX += cosf(mAngle) * mSpeed;
	mY -= sinf(mAngle) * mSpeed;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

	if (mRect.left <= 0)mAngle = 0;
	else if (mRect.right >= WINSIZEX)mAngle = PI;
}

void Enemy::UpdateFrame()
{
	mFrameCount++;
	if (mFrameCount >= 5)
	{
		mFrameCount = 0;
		mIndexX++;
		if (mIndexX >= mFrameMax)
			mIndexX = mStartFrameX;
	}
}
void Enemy::UpdateFrame(int time)
{
	mFrameCount++;
	if (mFrameCount >= time)
	{
		mFrameCount = 0;
		mIndexX++;
		if (mIndexX >= mFrameMax)
			mIndexX = mStartFrameX;
	}
}


//탄환관련 함수
void Enemy::UpdateBullet(EnemyBulletType type, int timing)
{
	if (mActive)
	{
		if (type == EnemyBulletType::Null)
			return;
		//mFiringFrameCount++;
		if (mFiringFrameCount % timing == 0)
		{
			float angle = mAngle;
			if (type == EnemyBulletType::Random)	//1
				angle = Random::GetInstance()->RandomInt(1, 360) * (180 / PI);
			if (type == EnemyBulletType::Target)	//2
				angle = PlayerAngle();
			mBulletManager->Fire(L"CircleBullet", mX, mY, 7.f, angle, 0, 0, Target::Player, type);
			//mFiringFrameCount = 0;
		}
	}
}
void Enemy::RowFire(float angle, float speed)
{
	if (mActive)
	{
		if (mFiringFrameCount % 70 <= 15 && mFiringFrameCount%3 ==0)
		{
			float newangle = angle;//PlayerAngle();
			mBulletManager->Fire(L"Row", mX, mY, 7.f, newangle, 0, 0, Target::Player, EnemyBulletType::Row);
			mShotCount++;
		}
	}
}
void Enemy::Row3Fire(float angle, float speed)
{
	if (mActive)
	{
		if (mFiringFrameCount % 70 <= 15 && mFiringFrameCount % 3 == 0)
		{
			float newangle = angle;//PlayerAngle();
			mBulletManager->Fire(L"Row", mX, mY, speed, newangle + (20*PI/180), 0, 0, Target::Player, EnemyBulletType::Row3);
			mBulletManager->Fire(L"Row", mX, mY, speed, newangle - (20 * PI / 180), 0, 0, Target::Player, EnemyBulletType::Row3);
			mBulletManager->Fire(L"Row", mX, mY, speed, newangle, 0, 0, Target::Player, EnemyBulletType::Row3);

			mShotCount++;
		}
	}
}
void Enemy::CenterFire(int num, float speed, float startAngle)
{

	if (mActive)
	{
		//mFiringFrameCount++;
		if (mFiringFrameCount % 70 == 1)
		{
			for (int i = 0; i < num; ++i)
			{
				float angle = (360/num*i + startAngle) * (PI / 180);
				mBulletManager->Fire(L"Center", mX, mY, speed, angle, 0, 0, Target::Player, EnemyBulletType::Center);
			}
			//mFiringFrameCount = 0;
			mShotCount++;
		}
	}
}

void Enemy::TurnFire(float speed, float startAngle)
{
	if (mActive)
	{
		if (mFiringFrameCount % 70 == 40)
		{
			for (int i = 0; i < 15; ++i)
			{
				float angle = startAngle + (2 * i * PI / 180);
				mBulletManager->Fire(L"Turn", mX, mY, speed, angle, 0, 0, Target::Player, EnemyBulletType::Turn);
			}
			mShotCount++;
		}
	}
}

void Enemy::Turn()
{
	mBulletManager->TurnAngle();
}

void Enemy::HelixFire(float speed,float angle)
{
	if (mActive)
	{
		if (mFiringFrameCount % 8 == 1)
		{ 
			mBulletManager->Fire(L"Helix", mX, mY, speed, angle, 0, 0, Target::Player, EnemyBulletType::Turn);
		}
	}
}

void Enemy::DivideFire(float speed, float startAngle)
{
	if (mActive)
	{
		if (mFiringFrameCount % 40 == 1)
		{
			for (int i = 0; i < 20; ++i)
			{
				float angle = (360 / 20 * i + startAngle) * (PI / 180);
				mBulletManager->Fire(L"DivideBullet", mX, mY, speed, angle, 0, 0, Target::Player, EnemyBulletType::Divide);
			}
			mShotCount++;
		}
	}
}

void Enemy::Divide()
{
	mBulletManager->DivideBullet();
}
//탄환보조
void Enemy::AllFalse()
{
	mBulletManager->SetRangeFalse();
}

float Enemy::PlayerAngle()
{
	float pX = mPlayer->GetX();
	float pY = mPlayer->GetY();
	return Math::GetAngle(mX, mY, pX, pY);
}

//발사 범위 화면인지 확인
bool Enemy::CheckRange()	//어디? Enemy Update에서 에너미의 위치를 확인, 후에 파이어
{
	if (mX < PLAYLEFT) return false;
	else if (mX > PLAYRIGHT) return false;
	else if (mY < PLAYTOP) return false;
	else if (mY > PLAYBOTTOM) return false;
	else return true;
}

