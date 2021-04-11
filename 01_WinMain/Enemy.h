#pragma once
#include "Unit.h"
class Image;
class Bullet;
class Player;
class BulletManager;

const float sp = 5.f;

struct Point {
	float x;
	float y;
};

//상속 : 어떤 클래스로 부터 속성(변수,함수)을 이어받아서 클래스를 구현 하는 것
class Enemy : public Unit
{
protected:
	EnemyType mType;
	EnemyBulletType mBulletType;

	wstring mIname;
	int mStartFrameX;
	int mStartFrameY;
	int mFrameMax;
	int mFrameCount;

	int mFiringFrameCount;		//프레임재는 녀석

	int mMoveCount;				//움직임 제어할 타이밍
	int mShotCount;				//발사할 타이밍
	Player* mPlayer;
	BulletManager* mBulletManager;
public:
	void Init(int x, int y, int startX, int startY);
	virtual void Release()override;
	virtual void Update()override;
	virtual void Render(HDC hdc,bool isAlpha = false);

	inline void SetPlayerPtr(Player* player) { mPlayer = player; }
	inline void SetBulletManagerPtr(BulletManager* manager) { mBulletManager = manager; }

	inline void SetBulletType(EnemyBulletType type) { mBulletType = type; }
	inline EnemyType GetType()const { return mType; }
	inline wstring GetIname()const { return mIname; }
	

	void UpdateMove();
	void UpdateFrame();
	void UpdateFrame(int time);
	void UpdateBullet(EnemyBulletType type, int timing = 20);

	void RowFire(float angle,float speed = 5.f);
	void Row3Fire(float angle, float speed = 5.f);
	void CenterFire(int num = 20, float speed = 3.f, float startAngle = 0.f);
	void TurnFire(float speed = 2.f, float startAngle = 4.43f);
	void Turn();
	void HelixFire(float speed = 5.f, float angle = 4.68f);
	void DivideFire(float speed = 3.f, float startAngle = 0.f);
	void Divide();
	void AllFalse();

	inline float PlayerAngle();

	bool CheckRange();
};

