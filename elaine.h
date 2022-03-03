#pragma once
#include "gameNode.h"
class elaine : public gameNode
{
private:
public:
	elaine();
	~elaine();

	virtual HRESULT init();
	virtual void update();
	virtual void release();
	virtual void render();

};

