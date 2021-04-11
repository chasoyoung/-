#include "pch.h"
#include "BackGround.h"
#include "Image.h"
void BackGround::Init()
{
	mImage = ImageManager::GetInstance()->FindImage(L"Stage1Background");
	mBackShade = ImageManager::GetInstance()->FindImage(L"Shade1");

	bgWidth = PLAYX;
	bgHeight = PLAYY;
	bRect1 = RectMake(PLAYLEFT, PLAYTOP, PLAYX, PLAYY);
	bRect2 = RectMake(PLAYLEFT, PLAYTOP-PLAYY, PLAYX, PLAYY);

	mSpeed = 3.f;
}

void BackGround::Update()
{
	MoveRect(bRect1, 0, mSpeed, bgWidth, bgHeight);
	MoveRect(bRect2, 0, mSpeed, bgWidth, bgHeight);
}

void BackGround::Render(HDC hdc)
{
	mBackShade->ScaleRender(hdc, PLAYLEFT, PLAYTOP, bgWidth, bgHeight);
	mImage->AlphaScaleRender(hdc,bRect1.left, bRect1.top, bgWidth, bgHeight, 0.45f);
	mImage->AlphaScaleRender(hdc, bRect2.left, bRect2.top, bgWidth, bgHeight, 0.45f);
}

void BackGround::MoveRect(RECT &rect, int x, int y, int width, int height)
{
	rect.left += x;
	rect.top += y;

	if (rect.left > PLAYRIGHT)
		rect.left = PLAYLEFT - PLAYX;
	if (rect.top > PLAYBOTTOM)
		rect.top = PLAYTOP - PLAYY +3;
	rect = RectMake(rect.left,rect.top, width, height);


}
