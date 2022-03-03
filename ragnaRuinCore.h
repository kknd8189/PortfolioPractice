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

	virtual HRESULT init();			//초기화 함수
	virtual void release();			//메모리 해제 함슈
	virtual void update();			//연산하는 함수
	virtual void render();			//그리기 함수

	void pixelCollision();
	void cameraSetting();
};

