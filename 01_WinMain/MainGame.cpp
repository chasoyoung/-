#include "pch.h"
#include "MainGame.h"

#include "Image.h"
#include "BackGround.h"

#include "IntersectManager.h"

#include "Player.h"

#include "BulletManager.h"
#include "Enemy.h"
#include "EnemyManager.h"

void MainGame::Init()
{
	SetTimer(_hWnd, 1, 10, NULL);

	//이미지
	mBackBuffer = new Image();
	mBackBuffer->CreateEmpty(WINSIZEX, WINSIZEY);

	ImageManager::GetInstance()->Init();	//이미지 로드

	//UI
	mFront = ImageManager::GetInstance()->FindImage(L"Front");
	Hp = ImageManager::GetInstance()->FindImage(L"Hp");
	Spell = ImageManager::GetInstance()->FindImage(L"Spell");
	mTitle = ImageManager::GetInstance()->FindImage(L"Title");
	mClear = ImageManager::GetInstance()->FindImage(L"Clear");

	//스테이지배경
	mBackGround = new BackGround();
	mBackGround->Init();

	//플레이어
	mPlayer = new Player();
	mPlayer->Init();
	//manager
	mBulletManager = new BulletManager();
	mBulletManager->Init();

	mEnemyManager = new EnemyManager();
	mEnemyManager->SetBulletManagerPtr(mBulletManager);
	mEnemyManager->SetPlayerPtr(mPlayer);

	mPlayer->SetEnemyManagerPtr(mEnemyManager);
	mPlayer->SetBulletManagerPtr(mBulletManager);

	mIntersectManager = new IntersectManager();
	mIntersectManager->Init();
	mIntersectManager->SetPlayerPtr(mPlayer);
	mIntersectManager->SetBulletManagerPtr(mBulletManager);
	mIntersectManager->SetEnemyManagerPtr(mEnemyManager);

	//적은 페이즈별로 생성
	mEnemyManager->Init();
	//SetPhase1();

	//메인게임 변수
	mPhase = mCheck = 0;
	mRuntime = 0;
	mFrameCount = 0;
	mFrameX = 0;

	isStart = false;
	isClear = true;
}

void MainGame::Release()
{
	KillTimer(_hWnd, 1);

	Random::ReleaseInstance();	//싱글톤 인스턴스 삭제

	SafeDelete(mBackBuffer);

	//배경 삭제
	SafeDelete(mBackGround);

	//유닛
	mPlayer->Release();
	SafeDelete(mPlayer);

	mBulletManager->Release();
	SafeDelete(mBulletManager);

	mIntersectManager->Release();
	SafeDelete(mIntersectManager);

	//적 인스턴스 삭제
	mEnemyManager->Release();
	SafeDelete(mEnemyManager);

}


void MainGame::Update()
{
	if ((isStart == false || isClear == true )&& Input::GetInstance()->GetKeyDown(VK_RETURN))
	{
		isStart = true;
		isClear = false;

	}
	if ( isStart && !isClear )
	{

		CheckPhase();
		CheckChange();

		//Class Update
		mPlayer->Update();
		mEnemyManager->Update(mRuntime, mPhase);
		mBulletManager->Update();
		mIntersectManager->Update(mPhase);
		mBackGround->Update();

		//Game
		mRuntime++;
		
		if (mPlayer->GetHp() <= 0 || isClear)
		{
			Release();
			if (isClear)
			{
				Init();
				isStart = true;
				isClear = true;
			}
			else
			{
				Init();
			}
		}
		
	}
}

void MainGame::Render(HDC hdc)
{
	HDC backDC = mBackBuffer->GetHDC();
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	// ==================================================
	{
		mBackGround->Render(backDC);	//배경
		mBulletManager->Render(backDC);	//적 탄환
		mIntersectManager->Render(backDC);//이팩트
		mPlayer->Render(backDC);		//플레이어
		mEnemyManager->Render(backDC);	//적



		mFront->ScaleRender(backDC, 0, 0, WINSIZEX, WINSIZEY);	//UI
		for (int i = 0; i < mPlayer->GetHp(); ++i)
			Hp->FrameRender(backDC, 845 + i*30,135,0,0);
		for(int i = 0; i < mPlayer->GetSpell(); ++i)
			Spell->FrameRender(backDC, 845 + i * 30, 200, 0, 0);


		//wstring phase = L"현재 페이즈 : " + to_wstring(mPhase);
		//TextOut(backDC, 800, 40, phase.c_str(), phase.length());
		//wstring size = L"Enemy크기 : " + to_wstring(mEnemyManager->GetListsize());
		//TextOut(backDC, 800, 100, size.c_str(), size.length());
		if (mEnemyManager->GetListsize() > 0 && mEnemyManager->GetList()[0]->GetType() == EnemyType::Boss)
		{
			float hp = (mEnemyManager->GetList()[0]->GetHp() / 10 +1)* 6.25;
			HBRUSH red = CreateSolidBrush(RGB(200, 0, 0));
			HBRUSH prevBrush = (HBRUSH)SelectObject(backDC, red);
			RECT temp = RectMake(PLAYLEFT, PLAYTOP, hp, 20);
			RenderRect(backDC,temp);
			SelectObject(backDC, prevBrush);
			DeleteObject(red);
		}

		if (!isStart)
			mTitle->ScaleRender(backDC, 0, 0, WINSIZEX, WINSIZEY);
		else if (isClear)
			mClear->Render(backDC,0,0);
			
	}
	//====================================================
	mBackBuffer->Render(hdc, 0, 0);
}

void MainGame::CheckPhase()
{
	if (mPhase == 0 && mRuntime >= 1000)
	{
		//mEnemyManager->Release();
		mRuntime = 0;
		mPhase = 1;
		return;
	}

	if (mEnemyManager->GetListsize() > 0 && mEnemyManager->GetList()[0]->GetType() == EnemyType::Boss)
	{
		int hp = mEnemyManager->GetList()[0]->GetHp();
		if (hp < bosshp / 4)
		{
			mPhase = 4;
			return;
		}
		else if (hp < bosshp / 4 * 2)
		{
			mPhase = 3;
			return;
		}
		else if (hp < bosshp / 4 * 3)
		{
			mPhase = 2;
			return;
		}
		else if (hp < bosshp)
		{
			mPhase = 1;
			return;
		}
	}
}

void MainGame::CheckChange()
{
	if (mPhase != mCheck)
	{

		mRuntime = 1;
		if (mPhase != 1)
		{
			for (int i = 0; i < mEnemyManager->GetListsize(); ++i)
			{
				if(mEnemyManager->GetList()[i]->GetType() != EnemyType::Boss)
					mEnemyManager->IndexRelease(i);
			}
			mBulletManager->SetRangeFalse();
		}

		if (mCheck == 4)
		{
			isClear = true;
		}else
			mCheck = mPhase;
	}
}