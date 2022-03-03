#pragma once
#pragma comment (lib, "Vfw32.lib")

#include "gameNode.h"
#include "RagnaRuin.h"
#include "ragnaRuinCore.h"
#include "battleScene.h"
#include "gameoverScene.h"
#include "title.h"


#include <Vfw.h>


class playGround : public gameNode
{
private:
	HWND _video;

public:
	playGround();
	~playGround();

	virtual HRESULT init();			//초기화 함수
	virtual void release();			//메모리 해제 함슈
	virtual void update();			//연산하는 함수
	virtual void render();			//그리기 함수

	
};

