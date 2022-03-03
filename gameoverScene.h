#pragma once
#include "gameNode.h"

class gameoverScene: public gameNode
{
private:
	int _alpha;

public:
	gameoverScene();
	~gameoverScene();

	HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	
};

