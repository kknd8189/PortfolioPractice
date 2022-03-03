#pragma once
#include "gameNode.h"
#include "player.h"
#include "gameData.h"

class RagnaRuin : public gameNode, public gameData
{
private:
	player* _player;

	int _probeY;
	int _probeX;
	int _randProb;
	int _randCount;


public:
	RagnaRuin();
	~RagnaRuin();

	virtual HRESULT init();			//�ʱ�ȭ �Լ�
	virtual void release();			//�޸� ���� �Խ�
	virtual void update();			//�����ϴ� �Լ�
	virtual void render();			//�׸��� �Լ�

	void pixelCollision();
	void cameraSetting();
	void randomEncounter();
};


