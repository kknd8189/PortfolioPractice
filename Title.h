#pragma once
#include "gameNode.h"


class title : public gameNode
{
private:
	RECT _newGameRc;

public:
	title();
	~title();

	virtual HRESULT init();			//�ʱ�ȭ �Լ�
	virtual void release();			//�޸� ���� �Խ�
	virtual void update();			//�����ϴ� �Լ�
	virtual void render();			//�׸��� �Լ�
};