#include "pch.h"
#include "Player.h"

#include "Image.h"
#include "Bullet.h"
#include "BulletManager.h"
#include "Enemy.h"
#include "EnemyManager.h"

void Player::Init()
{
	mImage = ImageManager::GetInstance()->FindImage(L"Player");
	mBack = ImageManager::GetInstance()->FindImage(L"SpellBack");

	mIndexX = 0;
	mIndexY = 0;
	mSizeX = mImage->GetFrameWidth();
	mSizeY = mImage->GetFrameHeight();


	mX = STARTX; 
	mY = STARTY;
	mType = UnitType::Player;

	mRect = RectMakeCenter(mX, mY, 10, 10);

	range = RectMakeCenter(mX, mY, 300, 300);

	mHp = 5;
	mSpell = 6;
	mSpeed = 6.f;
	mKeyFrame = 0;
	mAlpha = 0.f;

	mFrameCount = 0;

	mState = State::nomal;
	stateCount = 0;
}

void Player::Release()
{
	for (int i = 0; i < mBullets.size(); ++i)
	{
		SafeDelete(mBullets[i]);
	}
}

void Player::Update()
{
	if (mState == State::super)
		stateCount++;
	if (stateCount >= 100)
	{
		mState = State::nomal;
		stateCount = 0;
	}

	if (mAlpha > 0)
		mAlpha -= 0.05f;

	//키입력
	if (Input::GetInstance()->GetKey(VK_SHIFT))
	{
		mSpeed = 3.f;
	}
	if (Input::GetInstance()->GetKeyUp(VK_SHIFT))
	{
		mSpeed = 6.f;
	}
	if (Input::GetInstance()->GetKey(VK_LEFT))
	{
		Move(-mSpeed, 0);
	}
	else if (Input::GetInstance()->GetKey(VK_RIGHT))
	{
		Move(mSpeed, 0);
	}

	if (Input::GetInstance()->GetKey(VK_UP))
	{
		Move(0, -mSpeed);
	}
	else if (Input::GetInstance()->GetKey(VK_DOWN))
	{
		Move(0, mSpeed);
	}

	Modify();
	UpdateFrame();

	//탄환발사
	if (Input::GetInstance()->GetKeyDown('Z'))
	{
		NewBullet();
		mKeyFrame = 0;
	}
	if (Input::GetInstance()->GetKey('Z'))
	{
		mKeyFrame++;
		if (mKeyFrame >= 7)
		{
			NewBullet();
			mKeyFrame = 0;
		}
	}
	if (Input::GetInstance()->GetKeyDown(VK_SPACE))
	{
		if (mSpell > 0)
		{
			mBulletManager->SetRangeFalse(range);
			mSpell--;
			mAlpha = 1.f;
		}
	}

	for (int i = 0; i < mBullets.size(); ++i)
	{
		SetSpecialAngle();
		mBullets[i]->Update();
		if (mBullets[i]->GetX() <= PLAYLEFT)
		{
			RemoveBullet(i);
			continue;
		}
		if (mBullets[i]->GetX() >= PLAYRIGHT)
		{
			RemoveBullet(i);
			continue;
		}
		if (mBullets[i]->GetY() <= PLAYTOP)
		{
			RemoveBullet(i);
			continue;
		}
		if (mBullets[i]->GetY() >= PLAYBOTTOM)
		{
			RemoveBullet(i);
			continue;
		}
	}
}

void Player::Render(HDC hdc)
{
	mBack->AlphaScaleRender(hdc, range.left, range.top, 300, 300, mAlpha);

	for (int i = 0; i < mBullets.size(); ++i)
	{
		mBullets[i]->Render(hdc, true);
		//RenderRect(hdc, mBullets[i]->GetRect());
	}

	if(GetState() == State::nomal)
		mImage->FrameRender(hdc, mRect.left - (mSizeX / 4), mRect.top-(mSizeY/2),mIndexX,mIndexY);
	else if(GetState() == State::super)
		mImage->AlphaFrameRender(hdc, mRect.left - (mSizeX / 4), mRect.top - (mSizeY / 2), mIndexX, mIndexY,0.3f);
	//RenderRect(hdc, mRect);
}

void Player::UpdateFrame()
{
	mFrameCount++;
	if (mFrameCount >= 5)
	{
		mFrameCount = 0;
		mIndexX++;
		if (mIndexX >= 4)
			mIndexX = 0;
	}
}

//이동관련 함수
void Player::Move(float moveX, float moveY)
{
	mX += moveX;
	mY += moveY;
	mRect = RectMakeCenter(mX, mY, 10, 10);
	range = RectMakeCenter(mX, mY, 300, 300);
}
void Player::Modify()
{
	if (mX + mSizeX / 2 > PLAYRIGHT)
		mX = PLAYRIGHT - mSizeX / 2;
	else if (mX - mSizeX / 2 < PLAYLEFT)
		mX = PLAYLEFT + mSizeX / 2;
	if (mY + mSizeY / 2 > PLAYBOTTOM)
		mY = PLAYBOTTOM - mSizeY / 2;
	else if (mY - mSizeY /2 < PLAYTOP)
		mY = PLAYTOP + mSizeY / 2;
	mRect = RectMakeCenter(mX, mY, 10, 10);
}

//탄환관련 함수
void Player::RemoveBullet(int index)
{
	if (mBullets.size() <= index)return;

	SafeDelete(mBullets[index]);
	mBullets.erase(mBullets.begin() + index);
}
void Player::NewBullet()
{
	Image* bulletImage = ImageManager::GetInstance()->FindImage(L"PlayerBullet");
	for (int i = 0; i < 6; ++i)
	{
		Bullet* bullet = new Bullet;
		if(i == 0 || i == 5)
			bullet->Fire(bulletImage, mX - 50 + 20 * i, mY, 10.f, PI / 2.f, 0, 0, Target::Enemy, UnitType::SpecialBullet);
		else
			bullet->Fire(bulletImage, mX - 50 + 20 * i, mY, 10.f, PI / 2.f,0,1, Target::Enemy, UnitType::NomalBullet);
		mBullets.push_back(bullet);
	}
}

void Player::SetSpecialAngle()
{
	for (int i = 0; i < mBullets.size(); ++i)
	{
		if (mBullets[i]->GetType() == UnitType::SpecialBullet)
		{
			mEnemys = mEnemyManager->GetList();
			for (int j = 0; j < mEnemys.size(); ++j)
			{
				RECT Back = RectMake(PLAYLEFT, PLAYTOP, PLAYX, PLAYY);
				RECT temp;
				RECT erect = mEnemys[j]->GetRect();
				if (IntersectRect(&temp, &erect, &Back))
				{
					float angle = Math::GetAngle(mBullets[i]->GetX(), mBullets[i]->GetY(), mEnemys[j]->GetX(), mEnemys[j]->GetY());
					mBullets[i]->SetAngle(angle);
					break;
				}
			}

		}
	}
}
