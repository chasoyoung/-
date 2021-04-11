#include "pch.h"
#include "IntersectManager.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "EnemyManager.h"
#include "BulletManager.h"
#include "FrameEffect.h"

void IntersectManager::Init()
{
	for (int i = 0; i < 100; ++i)
	{
		FrameEffect* effect = new FrameEffect();
		effect->Init();
		mEffectList.push_back(effect);
	}
}

void IntersectManager::Render(HDC hdc)
{
	for (int i = 0; i < mEffectList.size(); ++i)
	{
		if (mEffectList[i]->GetActive())
		{
			mEffectList[i]->Render(hdc);
		}
	}
}

void IntersectManager::Release()
{
	for (int i = 0; i < mEffectList.size(); ++i)
	{
		SafeDelete(mEffectList[i]);
		mEffectList.erase(mEffectList.begin() + i);
	}
}

//이펙트 위치를 넣음
void IntersectManager::SetEffect(float x, float y)
{
	for (int i = 0; i < mEffectList.size(); ++i)
	{
		if (mEffectList[i]->GetActive() == false)
		{
			mEffectList[i]->SetRect(x, y);
			break;
		}
	}
}

void IntersectManager::Update(int &phase)
{
	mEnemys = mEnemyManager->GetList();
	mEnemyBullets = mBulletManager->GetList();
	mPlayerBullets = mPlayer->GetBulletList();
	PlayertoEnemy(phase);
	EnemytoPlayer();
	EnemyPlayer();

	for (int i = 0; i < mEffectList.size(); ++i)
	{
		if (mEffectList[i]->GetActive() == true)
		{
			mEffectList[i]->FrameUpdate();
		}
	}
}


void IntersectManager::EnemytoPlayer()	//플레이어가 탄환을 맞는 판정 -> 액티브 false가 되면 출력 + Update정지
{
	if (mPlayer->GetState() == State::nomal)
	{
		RECT temp;
		RECT pRect = mPlayer->GetRect();
		for (int i = 0; i < mEnemyBullets.size(); ++i)
		{
			RECT bRect = mEnemyBullets[i]->GetRect();
			if (mEnemyBullets[i]->GetTarget() == Target::Player)
			{
				if (IntersectRect(&temp, &pRect, &bRect))
				{
					mEnemyBullets[i]->SetActive(false);
					mPlayer->UpdateHp(-1);
					mPlayer->SetState(State::super);
					break;
				}
			}
		}
	}
}

void IntersectManager::PlayertoEnemy(int &phase)	//적이 플레이어의 탄환을 맞는 판정
{
	RECT temp;
	for (int i = 0; i < mPlayerBullets.size(); ++i)
	{
		RECT bRect = mPlayerBullets[i]->GetRect();
		if (mPlayerBullets[i]->GetTarget() == Target::Enemy)
		{
			for (int j = 0; j < mEnemys.size(); ++j)
			{
				RECT eRect = mEnemys[j]->GetRect();
				if (IntersectRect(&temp, &eRect, &bRect))
				{
					float x = mPlayerBullets[i]->GetX();
					float y = mPlayerBullets[i]->GetY();
					SetEffect(x, y);

					mEnemys[j]->UpdateHp(-1);
					if (mEnemys[j]->GetHp() <= 0) 
					{
						if (mEnemys[j]->GetType() == EnemyType::Boss)
							phase++;
						mEnemyManager->IndexRelease(j);
						mEnemys.erase(mEnemys.begin() + j);
						j--;
					}
					mPlayer->RemoveBullet(i);
					mPlayerBullets.erase(mPlayerBullets.begin() + i);
					i--;
					break;
				}
			}
		}
	}
}

void IntersectManager::EnemyPlayer()
{
	if (mPlayer->GetState() == State::nomal)
	{
		RECT temp;
		RECT pRect = mPlayer->GetRect();
		for (int j = 0; j < mEnemys.size(); ++j)
		{
			RECT eRect = mEnemys[j]->GetRect();
			if (IntersectRect(&temp, &eRect, &pRect))
			{
				mEnemys[j]->UpdateHp(-1);
				if (mEnemys[j]->GetHp() <= 0)
				{
					mEnemyManager->IndexRelease(j);
					mEnemys.erase(mEnemys.begin() + j);
					j--;
				}
				mPlayer->UpdateHp(-1);
				mPlayer->SetState(State::super);
				break;
			}
		}
	}
}
