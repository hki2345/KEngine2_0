#pragma once
#include "KInitiator.h"

// �̹� ���� ���ο� "�̽ÿ�����" �ý���
// "�̽ôϿ�����"�� ���� ����� Ŭ�� ��������
// �� �̴Ͻÿ����͸� ��ӹ޾� [����] ��Ű���� �Ѵ�.
// �� �̴Ͻÿ����ʹ� ���� �ܰ� �����Ӹ� �ƴ϶� ��, ������Ʈ �� ��� ���� ���δ�.
// �� �޴��� ���� �̱������� �� �༮���� �������� - �������̽��� �����ϴ� �ɷ� ����
class KRenderer : public KInitiator
{
public:
	KRenderer();
	KRenderer(const KRenderer& _Core) = delete;
	KRenderer(const KRenderer&& _Core) = delete;
	void operator=(const KRenderer& _Core) = delete;
	virtual ~KRenderer() = 0;


public:
	virtual bool init() override = 0;
	virtual void render() = 0;
};

