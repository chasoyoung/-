#pragma once

class Image;
class Player;
class Enemy;
class EnemyManager;
class BulletManager;
class IntersectManager;
class BackGround;

class MainGame
{
	Image* mBackBuffer;
private:
	//Image* mBackground;
	//Image* mExplosion;
	Image* mFront;
	Image* Hp;
	Image* Spell;
	Image* mTitle;
	Image* mClear;

	BackGround* mBackGround;
	Player* mPlayer;	//include player's Bullet

	BulletManager* mBulletManager;	//enemy's Bullet
	EnemyManager* mEnemyManager;	//enemyList of All
	IntersectManager* mIntersectManager;

	int mRuntime;
	int mCheck;
	int mPhase;
	int mFrameCount;
	int mFrameX;

	bool isStart;
	bool isClear;
public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void CheckPhase();

	void CheckChange();


	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
};

