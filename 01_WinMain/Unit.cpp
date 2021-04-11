#include "pch.h"
#include "Unit.h"

#include "Image.h"
void Unit::Release()
{
}

void Unit::Update()
{
}

void Unit::Render(HDC hdc)
{
	mImage->Render(hdc, mRect.left, mRect.top);
}

bool Unit::CheckRange()
{
	if (mX < PLAYLEFT) return false;
	else if (mX > PLAYRIGHT) return false;
	else if (mY < PLAYTOP) return false;
	else if (mY > PLAYBOTTOM) return false;
	else return true;
}
