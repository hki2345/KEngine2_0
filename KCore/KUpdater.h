#pragma once




// 이번 버전 새로운 "업데이터" 시스템
// "업데이터"를 따로 만들어 클라나 에딧에서
// 그 업데이터를 상속받아 발진시키도록 한다.
// 단 메니저 같이 싱글톤으로 될 녀석들은 못씀ㅇㅇ
// 이 업데이터는 엔진 단계 최신화 뿐만 아니라 씬, 오브젝트 등 모든 곳에 쓰인다.
class KUpdater
{
public:
	KUpdater();
	virtual ~KUpdater() = 0;


public:
	virtual void update() = 0;
};

