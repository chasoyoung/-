#pragma once
#include "GameObject.h"
class Image;
class ImageManger;

class BackGround : public GameObject
{
	Image* mImage;
	Image* mBackShade;
	RECT bRect1,	//배경이미지
		 bRect2,
		 aRect1,	//장식,텍스쳐
		 aRect2,
		 aRect3;
	
	int bgWidth;
	int bgHeight;
public:
	virtual void Init()override;
	virtual void Update()override;
	virtual void Render(HDC hdc)override;
	void MoveRect(RECT& rect, int x, int y, int width, int height);
};

