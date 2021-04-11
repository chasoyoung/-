#pragma once
#include "GameObject.h"
class Bullet;
class Enemy;
class Player;
class BulletManager;
class EnemyManager;
class FrameEffect;

class IntersectManager : public GameObject
{
	Player* mPlayer;
	BulletManager* mBulletManager;
	EnemyManager* mEnemyManager;
	vector<Bullet*> mPlayerBullets;
	vector<Bullet*> mEnemyBullets;
	vector<Enemy*> mEnemys;
	vector<FrameEffect*> mEffectList;
public:
	//void Release();
	void SetPlayerPtr(Player* player) { mPlayer = player; }
	void SetEnemyManagerPtr(EnemyManager* enemy) { mEnemyManager = enemy; }
	void SetBulletManagerPtr(BulletManager* bullets) { mBulletManager = bullets; };

	void Init();
	void Render(HDC hdc);
	void Release();

	void SetEffect(float x, float y);

	void Update(int &phase);
	void EnemytoPlayer();
	void PlayertoEnemy(int &phase);
	void EnemyPlayer();
};

