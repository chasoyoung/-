#pragma once

class Image;
class Bullet;
class BulletManager
{
	bool turn;
	vector<Bullet*> mBullets;	//모든 Enemy의 탄환이 담겨있음, 플레이어껀 X
public:
	void Init();
	void Release();
	void IndexRelease(int index);
	void Update();
	void Render(HDC hdc);

	void Fire(wstring key, float x, float y, float speed, float angle,
				int indexX, int indexY, Target target, EnemyBulletType type);
	void TurnAngle();
	void DivideBullet();
	void SetRangeFalse(RECT range = RectMake(PLAYLEFT,PLAYTOP,PLAYX,PLAYY));
	inline vector<Bullet*> GetList() { return mBullets; };

};

