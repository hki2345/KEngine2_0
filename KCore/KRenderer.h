#pragma once


// �̹� ���� ���ο� "�̽ÿ�����" �ý���
// "�̽ôϿ�����"�� ���� ����� Ŭ�� ��������
// �� �̴Ͻÿ����͸� ��ӹ޾� [����] ��Ű���� �Ѵ�.
// �� �̴Ͻÿ����ʹ� ���� �ܰ� �����Ӹ� �ƴ϶� ��, ������Ʈ �� ��� ���� ���δ�.
// �� �޴��� ���� �̱������� �� �༮���� �������� - �������̽��� �����ϴ� �ɷ� ����
class KRenderer
{
public:
	KRenderer() {};
	KRenderer(const KRenderer& _Core) = delete;
	KRenderer(const KRenderer&& _Core) = delete;
	void operator=(const KRenderer& _Core) = delete;
	virtual ~KRenderer() = 0;


public:
	virtual void render() = 0;
};

