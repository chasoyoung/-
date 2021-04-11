#pragma once
#include "Unit.h"

class Image;

class Bullet;
class BulletManager;
class Enemy;
class EnemyManager;



class Player : public Unit
{
	Image* mBack;

	int mSpell;
	int mKeyFrame;
	float mAlpha;
	RECT range;

	State mState;
	int stateCount;

	vector<Bullet*> mBullets;	//플레이어 탄환
	BulletManager* mBulletManager;
	vector<Enemy*> mEnemys;
	EnemyManager* mEnemyManager;
public:
	void Init();
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	void UpdateFrame();

	void Move(float moveX, float moveY);

	void Modify();

	inline int GetSpell()const { return mSpell; }

	inline vector<Bullet*> GetBulletList()const { return mBullets; }
	void RemoveBullet(int index);
	void NewBullet();
	inline void SetSpecialAngle();
	inline void SetBulletManagerPtr(BulletManager* bullet) { mBulletManager = bullet; }
	inline void SetEnemyManagerPtr(EnemyManager* enemy) { mEnemyManager = enemy; }

	inline State GetState()const { return mState; }
	inline void SetState(State state) { mState = state; }
};

