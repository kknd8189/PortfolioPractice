#pragma once
#include "gameNode.h"


class aniTest : public gameNode
{
private:
	image* _camel;

	animation* _ani1;
	animation* _ani2;
	animation* _ani3;

public:
	aniTest();
	~aniTest();

	virtual HRESULT init();			//초기화 함수
	virtual void release();			//메모리 해제 함슈
	virtual void update();			//연산하는 함수
	virtual void render();			//그리기 함수
};

