#pragma once
enum class UnitType : int
{
	Player,
	Enemy,
	NomalBullet,
	SpecialBullet,
	EnemyBullet
};
enum class Target : int
{
	Player,
	Enemy
};
enum class EnemyType : int
{
	Roll,	//�߻�x �¿� �̵�
	Normal,	//����1
	Leader,	//źȯ����ü �ް���� ����
	Creater,	//���� ������ źȯ����ü
	Boss	//����
};
enum class EnemyBulletType : int
{
	Null,	//���ʹ��� ź�� �ƴ�
	Nomal,
	Random,	//1
	Row,
	Row3,	//3
	Turn,	//4
	Center,	//5
	Helix,	//6
	Divide,	//7

	Target,	//2
	Chase,	//�� ó�� �߻翡 �÷��̾� ��ġ ã��

	
};
enum class State : int
{
	nomal,
	super
};