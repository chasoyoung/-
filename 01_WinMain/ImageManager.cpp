#include "pch.h"
#include "ImageManager.h"

#include "Image.h"

ImageManager::~ImageManager()
{
	ImageIter iter = mImageList.begin();
	for (; iter != mImageList.end(); ++iter)
	{
		SafeDelete(iter->second);
	}
}

void ImageManager::Init()
{

	//총알의 경우 Frame00로 되어있으니 프레임이 없는 이미지라도 프레임 1,1로 지정하기
	//총알
	GetInstance()
		->LoadFromFile(L"CircleBullet", Resources(L"bullet.bmp"), 21, 21, 1, 1, true);
	GetInstance()
		->LoadFromFile(L"DivideBullet", Resources(L"DivideBullet0.bmp"), 28, 26, 1, 1, true);
	GetInstance()
		->LoadFromFile(L"Up", Resources(L"DivideBullet1.bmp"), 26, 28, 1, 1, true);
	GetInstance()
		->LoadFromFile(L"Down", Resources(L"DivideBullet2.bmp"), 26, 30, 1, 1, true);
	GetInstance()
		->LoadFromFile(L"Center", Resources(L"center.bmp"), 27, 30, 1, 1, true);
	GetInstance()
		->LoadFromFile(L"Row", Resources(L"row.bmp"), 14, 17, 1, 1, true);
	GetInstance()
		->LoadFromFile(L"Turn", Resources(L"turn.bmp"), 32, 33, 1, 1, true);
	GetInstance()
		->LoadFromFile(L"Helix", Resources(L"helix.bmp"), 21, 28, 1, 1, true);

	GetInstance()
		->LoadFromFile(L"Bullet", Resources(L"missile.bmp"), 416, 64, 13, 1, true);

	//배경
	GetInstance()
		->LoadFromFile(L"Shade1", Resources(L"shade1.bmp"), 600, 720, true);
	GetInstance()->
		LoadFromFile(L"Stage1Background", Resources(L"stg1bg.bmp"), 512, 512, true);
	GetInstance()
		->LoadFromFile(L"Title", Resources(L"title.bmp"), 640, 480, 1, 1, true);
	GetInstance()
		->LoadFromFile(L"Clear", Resources(L"clear.bmp"), 1080, 720, 1, 1, true);

	//UI
	GetInstance()
		->LoadFromFile(L"Front", Resources(L"front.bmp"), 1080, 720, true);
	GetInstance()
		->LoadFromFile(L"Hp", Resources(L"hp.bmp"), 28, 26, 1, 1, true);
	GetInstance()
		->LoadFromFile(L"Spell", Resources(L"spell.bmp"), 24, 24, 1, 1, true);
	GetInstance()
		->LoadFromFile(L"Title", Resources(L"title.bmp"), 640, 480, true);

	GetInstance()
		->LoadFromFile(L"Effect", Resources(L"effect.bmp"), 360, 42, 8, 1, true);

	//플레이어
	GetInstance()
		->LoadFromFile(L"SpellBack", Resources(L"bakc.bmp"), 256, 256, 1, 1, true);
	GetInstance()
		->LoadFromFile(L"Player", Resources(L"player.bmp"), 120, 43, 4, 1, true);
	GetInstance()
		->LoadFromFile(L"PlayerBullet", L"../02_Resources/PlayerBullet.bmp", 80, 40, 4, 2, true);

	//적
	GetInstance()
		->LoadFromFile(L"Roll", Resources(L"roll.bmp"), 220, 55, 4, 1, true);
	GetInstance()
		->LoadFromFile(L"Nomal", Resources(L"nomal.bmp"), 152, 38, 4, 1, true);
	GetInstance()
		->LoadFromFile(L"Leader", Resources(L"leader.bmp"), 196, 65, 3, 1, true);
	GetInstance()
		->LoadFromFile(L"Creater1", Resources(L"create1.bmp"), 1040, 130, 8, 1, true);
	GetInstance()
		->LoadFromFile(L"Creater", Resources(L"create0.bmp"), 480, 60, 8, 1, true);
	GetInstance()
		->LoadFromFile(L"Boss", Resources(L"boss.bmp"), 600, 130, 12, 2, true);
}

void ImageManager::LoadFromFile(wstring key, wstring filePath, int width, int height, bool isTrans, COLORREF transColor)
{
	ImageIter iter = mImageList.find(key);
	if (iter != mImageList.end())
	{
		return;
	}

	Image* newImage = new Image();
	newImage->LoadFromFile(filePath, width, height, isTrans, transColor);

	mImageList.insert(make_pair(key, newImage));
}

void ImageManager::LoadFromFile(wstring key, wstring filePath, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	ImageIter iter = mImageList.find(key);
	if (iter != mImageList.end())
	{
		return;
	}

	Image* newImage = new Image();
	newImage->LoadFromFile(filePath, width, height,frameX,frameY, isTrans, transColor);

	mImageList.insert(make_pair(key, newImage));
}

Image * ImageManager::FindImage(wstring key)
{
	ImageIter iter = mImageList.find(key);
	if (iter != mImageList.end())
	{
		return iter->second;
	}
	//nullptr : 0인데 포인터에서만 쓸 수 있는 0
	return NULL;
}
