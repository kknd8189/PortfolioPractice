#pragma once
#include "gameNode.h"

class valkyries : public gameNode
{
private:


public:
	valkyries();
	~valkyries();

	virtual HRESULT init();
	virtual HRESULT init(const char* imageName, POINT position);
	virtual void update();
	virtual void release();
	virtual void render();
	void draw();

};

