#include "pch.h"
#include "BulletManager.h"
#include "Image.h"
#include "Bullet.h"

void BulletManager::Init()
{
	for (int i = 0; i < 10000; ++i)
	{
		Bullet* bullet = new Bullet();
		bullet->SetActive(false);
		mBullets.push_back(bullet);
	}
	turn = false;
}

void BulletManager::Release()
{
	for (int i = 0; i < mBullets.size(); ++i)
	{
		SafeDelete(mBullets[i]);
		mBullets.erase(mBullets.begin() + i);
	}
}

void BulletManager::IndexRelease(int index)
{
	if (index >= mBullets.size()) return;

	SafeDelete(mBullets[index]);
	mBullets.erase(mBullets.begin() + index);
}

void BulletManager::Update()
{
	for (int i = 0; i < mBullets.size(); ++i)
	{
		if (mBullets[i]->GetActive())
		{
			mBullets[i]->Update();
			if ((mBullets[i]->GetY() < 0 || mBullets[i]->GetY() > PLAYBOTTOM)
				|| (mBullets[i]->GetX() < 0 || mBullets[i]->GetX() > PLAYRIGHT))
			{
				mBullets[i]->SetActive(false);
			}
		}
	}
}

void BulletManager::Render(HDC hdc)
{
	for (int i = 0; i < mBullets.size(); ++i)
	{
		if (mBullets[i]->GetActive())
		{
			if(mBullets[i]->GetEnemyBulletType() == EnemyBulletType::Turn)
				mBullets[i]->Render(hdc, true);
			else
				mBullets[i]->Render(hdc, false);
		}
	}
}

//발사 : Active를 True
void BulletManager::Fire(wstring key, float x, float y, float speed, float angle, int indexX, int indexY, Target target, EnemyBulletType type)
{
	Image* image = ImageManager::GetInstance()->FindImage(key);
	//Bullet* bullet = new Bullet();
	//bullet->Fire(image, x, y, speed, angle, indexX, indexY, target,type);

	//현재 활성화 안되어 있는 총알 찾기
	for (int i = 0; i < mBullets.size(); ++i)
	{
		//찾았다면
		if (mBullets[i]->GetActive() == false)
		{
			//mBullets[i] = bullet;
			mBullets[i]->Fire(image, x, y, speed, angle, indexX, indexY, target, type);
			mBullets[i]->SetActive(true);
			break;
		}
	}
}

void BulletManager::TurnAngle()
{
	for (int i = 0; i < mBullets.size(); ++i)
	{
		//찾았다면
		if (mBullets[i]->GetEnemyBulletType() == EnemyBulletType::Turn)
		{
			float angle;
			if(turn)
				angle = 1.68f;
			else
				angle = -1.68f;
			turn = !turn;
			mBullets[i]->SetAngle(mBullets[i]->GetAngle() + angle);
		}
	}
}

void BulletManager::DivideBullet()
{
	for (int i = 0; i < mBullets.size(); ++i)
	{
		//찾았다면
		if (mBullets[i]->GetEnemyBulletType() == EnemyBulletType::Divide)
		{
			int x = mBullets[i]->GetX();
			int y = mBullets[i]->GetY();
			Fire(L"Up", x, y, 3.5f, PI/2 , 0, 0, Target::Player, EnemyBulletType::Nomal);
			Fire(L"Down", x, y, 5.5f, PI + PI / 2, 0, 0, Target::Player, EnemyBulletType::Nomal);
			
			mBullets[i]->SetActive(false);
		}
	}
}

void BulletManager::SetRangeFalse(RECT range)
{
	RECT temp;

	for (int i = 0; i < mBullets.size(); ++i)
	{
		RECT brect = mBullets[i]->GetRect();
		//찾았다면
		if (mBullets[i]->GetActive() == true)
		{
			if(IntersectRect(&temp,&brect,&range))
				mBullets[i]->SetActive(false);
		}
	}
}
