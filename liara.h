#pragma once
#include "gameNode.h"
class liara : public gameNode
{
private:
public:
	liara();
	~liara();
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

