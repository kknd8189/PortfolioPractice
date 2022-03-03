#pragma once

#include "gameNode.h"
#include "userInterface.h"
#include "progressBar.h"
#include "kyle.h"


class enemyManager;

class userInterface : gameNode
{

private:


	kyle* _kyle;
	enemyManager* _em;

public:
	userInterface();
	~userInterface();

	HRESULT init();			//초기화 함수
	virtual void release();			//메모리 해제 함슈
	virtual void update();			//연산하는 함수
	virtual void render();			//그리기 함수

	int  getCameraX() { return _kyle->getCameraX(); }
	int  getCameraY(){ return _kyle->getCameraY(); }
	int  getKyleHP() { return _kyle->getKyleHP(); }
	void setCameraX(int x) { _kyle->setCameraX(x); }
	void setCameraY(int y) { _kyle->setCameraY(y); }

	void setEmMemoryAddressLink(enemyManager* em) { _em = em; }

};