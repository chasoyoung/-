#pragma once
class FrameEffect
{
	float mX;
	float mY;
	float mSizeX;
	float mSizeY;
	float mAngle;
	float mSpeed;
	RECT mRect;
	bool mActive;

	int mFrameCount;
	int mFrameUpdateCount;
	int mFrameIndexX;

	class Image* mImage;

	bool mIsEnd;	//³¡³µ³Ä????
public:
	void Init();
	void Render(HDC hdc);

	void FrameUpdate();
	void SetRect(float x, float y);

	void SetActive(bool active) { mActive = active; }
	bool GetActive()const { return mActive; }
	bool GetIsEnd()const { return mIsEnd; }
};

