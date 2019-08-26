#pragma once



// �̹� ���� ���ο� "�̽ÿ�����" �ý���
// "�̽ôϿ�����"�� ���� ����� Ŭ�� ��������
// �� �̴Ͻÿ����͸� ��ӹ޾� [����] ��Ű���� �Ѵ�.
// �� �̴Ͻÿ����ʹ� ���� �ܰ� �����Ӹ� �ƴ϶� ��, ������Ʈ �� ��� ���� ���δ�.
// �� �޴��� ���� �̱������� �� �༮���� �������� - �������̽��� �����ϴ� �ɷ� ����
class KInitiator
{
public:
	KInitiator();
	KInitiator(const KInitiator& _Core) = delete;
	KInitiator(const KInitiator&& _Core) = delete;
	void operator=(const KInitiator& _Core) = delete;
	virtual ~KInitiator() = 0;

private:
	virtual bool init() = 0;
};

