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

//��� : � Ŭ������ ���� �Ӽ�(����,�Լ�)�� �̾�޾Ƽ� Ŭ������ ���� �ϴ� ��
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

	int mFiringFrameCount;		//��������� �༮

	int mMoveCount;				//������ ������ Ÿ�̹�
	int mShotCount;				//�߻��� Ÿ�̹�
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

