#pragma once




// �̹� ���� ���ο� "��������" �ý���
// "��������"�� ���� ����� Ŭ�� ��������
// �� �������͸� ��ӹ޾� ������Ű���� �Ѵ�.
// �� �޴��� ���� �̱������� �� �༮���� ��������
// �� �������ʹ� ���� �ܰ� �ֽ�ȭ �Ӹ� �ƴ϶� ��, ������Ʈ �� ��� ���� ���δ�.
class KUpdater
{
public:
	KUpdater();
	KUpdater(const KUpdater& _Core) = delete;
	KUpdater(const KUpdater&& _Core) = delete;
	void operator=(const KUpdater& _Core) = delete;
	virtual ~KUpdater() = 0;


public:
	virtual void update() = 0;
};

