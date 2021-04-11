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
	Roll,	//발사x 좌우 이동
	Normal,	//요정1
	Leader,	//탄환생성체 달고오는 요정
	Creater,	//몬스터 옆에서 탄환생성체
	Boss	//보스
};
enum class EnemyBulletType : int
{
	Null,	//에너미의 탄이 아님
	Nomal,
	Random,	//1
	Row,
	Row3,	//3
	Turn,	//4
	Center,	//5
	Helix,	//6
	Divide,	//7

	Target,	//2
	Chase,	//맨 처음 발사에 플레이어 위치 찾음

	
};
enum class State : int
{
	nomal,
	super
};