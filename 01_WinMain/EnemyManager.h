#pragma once
class Enemy;
class Player;
class BulletManager;
class EnemyManager
{
	vector<Enemy*> mEnemyList;
	Player* mPlayer;
	BulletManager* mBulletManager;

	int mPhase;
public:
	void Init();
	void Init(Enemy* enemy, int x, int y, int startIndexX = 0, int startIndexY = 0);	//startX : 프레임 시작x, startY : 프레임 시작y
	//void Init(float x, float y, float spaseX, float spaseY, int num, wstring image, EnemyType type);
	void Release();
	void IndexRelease(int index);
	void Update(int time, int &phase);
	void Render(HDC hdc);

	void SetAngle(int index, float angle);
	void SetSpeed(int index, float speed);

	void TypeUpadte(EnemyType type);

	void SetPlayerPtr(Player* player) { mPlayer = player; }
	void SetBulletManagerPtr(BulletManager* manager) { mBulletManager = manager; }
	vector<Enemy*> GetList() { return mEnemyList; }
	int GetListsize() { return mEnemyList.size(); }

	void CreateEnemy(EnemyType type, int num, int startX, int startY, int startIndexX, int startIndexY,
					float angle = PI2, float speed = 5.f, bool getmaster = true);
	Enemy* CreateNomal(float x, float y);
	Enemy* CreaterLeader(float x);
	Enemy* CreateRoll(float angle, float speed);
	Enemy* CreateCreater(float x, float y, int num, int i, Enemy* master);
	Enemy* CreateBoss();
};

