#pragma once
#define PLAYLEFT 50
#define PLAYTOP 25
#define PLAYRIGHT 675
#define PLAYBOTTOM 700
#define PLAYX 625	//가로넓이
#define PLAYY 675	//세로높이
#define STARTX 350
#define STARTY 650

const int bosshp = 1000;

#define WINSTARTX 50
#define WINSTARTY 50
#define WINSIZEX 1080
#define WINSIZEY 720

//인자로 들어온 p를 삭제하고 NULL로 초기화 하는 매크로 함수, 안전하게 삭제
#define SafeDelete(p)\
{\
	if(p)\
	{\
		delete (p);\
		(p) = NULL;\
	}\
}

//싱글톤 매크로
#define Singleton(ClassName)\
public:\
static ClassName* GetInstance()\
{\
	static ClassName instance;\
	return &instance;\
}

#define Resources(Path) (wstring(L"../02_Resources/").append(Path))

//금술
#define Synthesize(VarType,VarName,FuncName)\
protected: VarType VarName;\
public: inline VarType Get##FuncName(void)const{return VarName;}\
public: inline void Set##FuncName(VarType value){VarName = value;}
