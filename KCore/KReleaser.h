#pragma once


// 이번 버전 새로운 "이시에이터" 시스템
// "이시니에이터"를 따로 만들어 클라나 에딧에서
// 그 이니시에이터를 상속받아 [발진] 시키도록 한다.
// 이 이니시에이터는 엔진 단계 발진뿐만 아니라 씬, 오브젝트 등 모든 곳에 쓰인다.
// 단 메니저 같이 싱글톤으로 될 녀석들은 못씀ㅇㅇ - 인터페이스를 같게하는 걸로 만족
class KReleaser
{
public:
	KReleaser();
	KReleaser(const KReleaser& _Core) = delete;
	KReleaser(const KReleaser&& _Core) = delete;
	void operator=(const KReleaser& _Core) = delete;
	virtual ~KReleaser() = 0;

public:
	virtual void release() = 0;
};

