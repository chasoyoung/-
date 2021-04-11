#pragma once
//���ӿ��� ���Ǵ� ������Ʈ���� �̳༮�� ��ӹ޴´�
//UI, �Ѿ�, ����, ������ ����
class GameObject
{
protected:
	float mX;
	float mY;
	float mSizeX;
	float mSizeY;
	float mSpeed;
	float mAngle;
	int mIndexX;
	int mIndexY;
	RECT mRect;
	int mHp;

	bool mActive;
	int mFrameCount;
public:
	virtual void Init() {}
	virtual void Release() {}
	virtual void Update() {}
	virtual void Render(HDC hdc) {}

	inline RECT GetRect()const { return mRect; }
	inline float GetX()const { return mX; }
	inline float GetY()const { return mY; }
	inline float GetSpeed()const { return mSpeed; }
	inline float GetSizeX()const { return mSizeX; }
	inline float GetSizeY()const { return mSizeY; }
	inline int GetHp()const { return mHp; }
	inline void UpdateHp(int hp) { mHp += hp; }

	inline void SetRect(RECT rect) { mRect = rect; }
	inline void SetX(float x) { mX = x; }
	inline void SetY(float y) { mY = y; }
	inline void SetSizeX(float size) { mSizeX = size; }
	inline void SetSizeY(float size) { mSizeY = size; }
	inline void SetHp(int hp) { mHp = hp; }
};

