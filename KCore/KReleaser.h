#pragma once


// �̹� ���� ���ο� "�̽ÿ�����" �ý���
// "�̽ôϿ�����"�� ���� ����� Ŭ�� ��������
// �� �̴Ͻÿ����͸� ��ӹ޾� [����] ��Ű���� �Ѵ�.
// �� �̴Ͻÿ����ʹ� ���� �ܰ� �����Ӹ� �ƴ϶� ��, ������Ʈ �� ��� ���� ���δ�.
// �� �޴��� ���� �̱������� �� �༮���� �������� - �������̽��� �����ϴ� �ɷ� ����
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

