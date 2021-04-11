#pragma once
#define PLAYLEFT 50
#define PLAYTOP 25
#define PLAYRIGHT 675
#define PLAYBOTTOM 700
#define PLAYX 625	//���γ���
#define PLAYY 675	//���γ���
#define STARTX 350
#define STARTY 650

const int bosshp = 1000;

#define WINSTARTX 50
#define WINSTARTY 50
#define WINSIZEX 1080
#define WINSIZEY 720

//���ڷ� ���� p�� �����ϰ� NULL�� �ʱ�ȭ �ϴ� ��ũ�� �Լ�, �����ϰ� ����
#define SafeDelete(p)\
{\
	if(p)\
	{\
		delete (p);\
		(p) = NULL;\
	}\
}

//�̱��� ��ũ��
#define Singleton(ClassName)\
public:\
static ClassName* GetInstance()\
{\
	static ClassName instance;\
	return &instance;\
}

#define Resources(Path) (wstring(L"../02_Resources/").append(Path))

//�ݼ�
#define Synthesize(VarType,VarName,FuncName)\
protected: VarType VarName;\
public: inline VarType Get##FuncName(void)const{return VarName;}\
public: inline void Set##FuncName(VarType value){VarName = value;}
