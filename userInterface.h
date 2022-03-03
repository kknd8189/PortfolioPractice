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

	HRESULT init();			//�ʱ�ȭ �Լ�
	virtual void release();			//�޸� ���� �Խ�
	virtual void update();			//�����ϴ� �Լ�
	virtual void render();			//�׸��� �Լ�

	int  getCameraX() { return _kyle->getCameraX(); }
	int  getCameraY(){ return _kyle->getCameraY(); }
	int  getKyleHP() { return _kyle->getKyleHP(); }
	void setCameraX(int x) { _kyle->setCameraX(x); }
	void setCameraY(int y) { _kyle->setCameraY(y); }

	void setEmMemoryAddressLink(enemyManager* em) { _em = em; }

};