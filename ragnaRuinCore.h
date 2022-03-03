#pragma once
#include "gameNode.h"
#include "player.h"


class ragnaRuinCore : public gameNode
{
private:
	player* _player;
	int _probeY;
	int _probeX;

public:
	ragnaRuinCore();
	~ragnaRuinCore();

	virtual HRESULT init();			//�ʱ�ȭ �Լ�
	virtual void release();			//�޸� ���� �Խ�
	virtual void update();			//�����ϴ� �Լ�
	virtual void render();			//�׸��� �Լ�

	void pixelCollision();
	void cameraSetting();
};

