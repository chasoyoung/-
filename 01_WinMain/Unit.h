#pragma once
#include "GameObject.h"

class Unit : public GameObject
{
protected:
	UnitType mType;
	EnemyBulletType mBType;
	float mOriginSpeed;
	float mSpeed;
	Image* mImage;
public:
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	bool CheckRange();

	inline float GetAngle()const { return mAngle; }
	inline void SetAngle(float angle) { mAngle = angle; }
	inline void SetSpeed(float speed) { mSpeed = speed; }
	inline bool GetActive()const { return mActive; }
	inline void SetActive(bool b) { mActive = b; }
	inline UnitType GetType()const { return mType; }
	inline EnemyBulletType GetEnemyBulletType()const { return mBType; }
};

