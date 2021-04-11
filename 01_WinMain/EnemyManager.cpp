#include "pch.h"
#include "EnemyManager.h"
#include "Enemy.h"
#include "EnemyKind.h"

void EnemyManager::Init()	//에너미 생성
{
}
void EnemyManager::Init(Enemy* enemy, int x, int y, int startIndexX, int startIndexY)
{
	enemy->Init(x, y, startIndexX, startIndexY);
	enemy->SetPlayerPtr(mPlayer);
	enemy->SetBulletManagerPtr(mBulletManager);
	mEnemyList.push_back(enemy);
}

//메모리 해제
void EnemyManager::Release()
{
	for (int i = 0; i < mEnemyList.size(); ++i)
	{
		SafeDelete(mEnemyList[i]);
		mEnemyList.erase(mEnemyList.begin() + i);
	}
}

void EnemyManager::IndexRelease(int index)
{
	if (mEnemyList.size() <= index)return;

	SafeDelete(mEnemyList[index]);
	mEnemyList.erase(mEnemyList.begin() + index);
}



//업데이트
void EnemyManager::Update(int time, int &phase)
{
	mPhase = phase;
	//에너미 생성
	
	if ( time >= 0 && phase == 1)
	{
		if(mEnemyList.size() == 0)
			CreateEnemy(EnemyType::Boss, 1, STARTX, 0, 0, 0, PI + PI / 2.f, 10.f);
	}

	if (phase == 0)
	{
		if (time % 300 == 55)
		{
			CreateEnemy(EnemyType::Normal, 5, 0, 0, 0, 0);
		}
		if (time % 300 == 80)
		{
			CreateEnemy(EnemyType::Normal, 5, 700, 0, 0, 0);
		}
		if (time % 300 == 299)
		{
			CreateEnemy(EnemyType::Roll, 5, 0, 300, 0, 0, PI2, 5.f);
		}
		if (time % 500 == 499)
		{
			CreateEnemy(EnemyType::Roll, 10, 700, 200, 0, 0, PI, 5.f);
		}

		if (time != 0 && time % 500 == 0)
		{
			CreateEnemy(EnemyType::Leader, 1, 200, 0, 0, 0);
			CreateEnemy(EnemyType::Creater, 1, STARTX, 100, 0, 0, 0, 5.f, true);
		}
		if (time != 0 && time % 600 == 0 )
		{
			CreateEnemy(EnemyType::Leader, 1, 600, 0, 0, 0);
			CreateEnemy(EnemyType::Creater, 1, STARTX, 100, 0, 0, 0, 5.f, true);
		}
		if (time != 0 && time % 550 == 0 )
		{
			CreateEnemy(EnemyType::Leader, 1, STARTX, 0, 0, 0);
			CreateEnemy(EnemyType::Creater, 1, STARTX, 100, 0, 0, 0, 5.f, true);
		}
	}


	if (mEnemyList.size() > 0 && mEnemyList[0]->GetType() == EnemyType::Boss)
	{
		if (time % 50 == 0 && phase == 2)
		{
			CreateEnemy(EnemyType::Creater, 1, STARTX, 100, 0, 0, 0, 5.f, false);
		}
		if (mEnemyList.size() == 1)
		{
			if (time >= 1 && phase == 3)
			{
				CreateEnemy(EnemyType::Creater, 3, STARTX, 100, 0, 0, 0, 5.f, true);
			}
		}

		if (time % 50 == 0 && phase == 4)
		{
			CreateEnemy(EnemyType::Creater, 1, STARTX, 100, 0, 0, 0, 5.f, false);
		}

		if (time != 0 && time % 500 == 0 && (phase == 0 || phase == 3))
		{
			CreateEnemy(EnemyType::Leader, 1, 200, 0, 0, 0);
			CreateEnemy(EnemyType::Creater, 1, STARTX, 100, 0, 0, 0, 5.f, true);
		}
		if (time != 0 && time % 450 == 0 && (phase == 0 || phase == 3))
		{
			CreateEnemy(EnemyType::Leader, 1, 600, 0, 0, 0);
			CreateEnemy(EnemyType::Creater, 1, STARTX, 100, 0, 0, 0, 5.f, true);
		}
		if (time != 0 && time % 550 == 0 && phase == 0)
		{
			CreateEnemy(EnemyType::Leader, 1, STARTX, 0, 0, 0);
			CreateEnemy(EnemyType::Creater, 1, STARTX, 100, 0, 0, 0, 5.f, true);
		}
	}

	//업데이트
	for (int i = 0; i < mEnemyList.size(); ++i)
	{
		mEnemyList[i]->Update();
		if (mEnemyList[i]->GetX() <=  -500)
		{
			IndexRelease(i);
			continue;
		}
		if (mEnemyList[i]->GetX() >= WINSIZEX + 500)
		{
			IndexRelease(i);
			continue;
		}
		if (mEnemyList[i]->GetY() <= -500)
		{
			IndexRelease(i);
			continue;
		}
		if (mEnemyList[i]->GetY() >= WINSIZEY)
		{
			IndexRelease(i);
			continue;
		}
	}
}

void EnemyManager::Render(HDC hdc)
{
	for (int i = 0; i < mEnemyList.size(); ++i)
	{
		if (mEnemyList[i] != NULL)
			mEnemyList[i]->Render(hdc);
	}
}

//에너미 생성
void EnemyManager::CreateEnemy(EnemyType type, int num, int startX, int startY, int startIndexX, int startIndexY,
								 float angle, float speed, bool getmaster)//, bool isRow)
{
	int x = startX;
	int y = startY;
	Enemy* e = new Enemy();
	if (type == EnemyType::Creater)
	{
		if (!getmaster)
		{
			e = NULL;
			if (mEnemyList[0]->GetType() == EnemyType::Boss)	//보스전일때 보스가 마스터
			{
				x = mEnemyList[0]->GetX();
				y = mEnemyList[0]->GetY();
			}
		}
		else
		{
			e = mEnemyList[mEnemyList.size() - 1];	//Creater 바로 앞에 있는게 마스터		
		}

		
	}
	for (int i = 0; i < num; ++i)
	{
		int randx = Random::GetInstance()->RandomInt(-40, 30);
		int randy = Random::GetInstance()->RandomInt(-30, 10);
		Enemy* enemy = new Enemy();
		switch (type)
		{
		case EnemyType::Roll:
			enemy = CreateRoll(angle, speed);
			break;
		case EnemyType::Normal:
			enemy = CreateNomal(x, y);
			break;
		case EnemyType::Leader:
			enemy = CreaterLeader(x);
			break;
		case EnemyType::Creater:
			enemy = CreateCreater(x, y, num, i,e);
			break;
		case EnemyType::Boss:
			enemy = CreateBoss();
			break;
		default:
			return;
		}
		Init(enemy, x+ i * randx, y + i * randy, startIndexX, startIndexY);
	}
}

Enemy* EnemyManager::CreateNomal(float x, float y)
{
	Nomal* ori = new Nomal();
	ori->Init(x, y);
	Enemy* enemy = ori;
	return enemy;
}
Enemy* EnemyManager::CreaterLeader(float x)
{
	Leader* ori = new Leader();
	ori->Init(x);
	Enemy* enemy = ori;
	return enemy;
}
Enemy* EnemyManager::CreateRoll(float angle, float speed)
{
	Roll* ori = new Roll();
	ori->Init(angle, speed);
	Enemy* enemy = ori;
	return enemy;
}
Enemy* EnemyManager::CreateCreater(float x, float y, int num, int i, Enemy* master)
{
	float angle = (360 / num * i) * (PI / 180);
	Creater* ori = new Creater();
	ori->Init(x, y, angle, master);
	Enemy* enemy = ori;
	return enemy;
}
Enemy* EnemyManager::CreateBoss()
{
	Boss* ori = new Boss();
	ori->Init();
	Enemy* enemy = ori;
	return enemy;
}

//기타 함수
void EnemyManager::SetAngle(int index, float angle)
{
	mEnemyList[index]->SetAngle(angle);
}

void EnemyManager::SetSpeed(int index, float speed)
{
	mEnemyList[index]->SetSpeed(speed);
}

void EnemyManager::TypeUpadte(EnemyType type)
{
	switch (type)
	{
	default:
		break;
	}
}

