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

	virtual HRESULT init();			//초기화 함수
	virtual void release();			//메모리 해제 함슈
	virtual void update();			//연산하는 함수
	virtual void render();			//그리기 함수

	void pixelCollision();
	void cameraSetting();
	void randomEncounter();
};


