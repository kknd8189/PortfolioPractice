#pragma once
#include "gameNode.h"


class title : public gameNode
{
private:
	RECT _newGameRc;

public:
	title();
	~title();

	virtual HRESULT init();			//초기화 함수
	virtual void release();			//메모리 해제 함슈
	virtual void update();			//연산하는 함수
	virtual void render();			//그리기 함수
};