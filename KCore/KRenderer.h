#pragma once
#include "KComponent.h"
#include "KVector.h"

// �̹� ���� ���ο� "�̽ÿ�����" �ý���
// "�̽ôϿ�����"�� ���� ����� Ŭ�� ��������
// �� �̴Ͻÿ����͸� ��ӹ޾� [����] ��Ű���� �Ѵ�.
// �� �̴Ͻÿ����ʹ� ���� �ܰ� �����Ӹ� �ƴ϶� ��, ������Ʈ �� ��� ���� ���δ�.
// �� �޴��� ���� �̱������� �� �༮���� �������� - �������̽��� �����ϴ� �ɷ� ����
class KTransform;
class KRenderer : public KComponent
{
public:
	KRenderer();
	KRenderer(const KRenderer& _Core) = delete;
	KRenderer(const KRenderer&& _Core) = delete;
	void operator=(const KRenderer& _Core) = delete;
	virtual ~KRenderer() = 0;



protected:
	KTransform* MyTrans;
	KPos2 MyPivot;

public:
	virtual bool init() override;
	virtual void update() override {};

	virtual void render() = 0;
	virtual void release() override {};

	inline void pivot(const KPos2& _Pivot)
	{
		MyPivot = _Pivot;
	}
};

